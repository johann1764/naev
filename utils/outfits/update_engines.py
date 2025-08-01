#!/usr/bin/env python3

import math
from sys import stderr, stdout, stdin
from outfit import nam2fil, outfit, MOBILITY_PARAMS
from getconst import PHYSICS_SPEED_DAMP


AG_EXP  = 0.25
TURN_CT = 0.43
STD_R   = 0.12
R_MAG   = 1.5

line_stats = {
    'Tricon' : {
        'speed_rank_offset' : 0.0,     # 0.0 indicates current speed rank
                                       # 1.0 means next speed rank (size+1);
                                       # !!! higher means slower
        'ratio' : 1.4,
    },
    'Krain' : {
        'speed_rank_offset' : -0.35,   # Between this size and size-1
        'ratio' : 1.1,
        'turn' : 1.05
    },
    'Nexus' : {
        'speed_rank_offset' : +0.15,   # Pretty good but slightly slower top speed
                                       # than Melendez and Tricon
        'ratio' : 1.0,
    },
    'Melendez' : {
        'speed_rank_offset' : +0.15,
        'ratio' : 0.5,
    },
    'Unicorp' : {
        'speed_rank_offset' : +0.45,
        'ratio' : 1.0,
    },
    "Za'lek" : {                       # TODO make these change over time the profile via Lua
        'speed_rank_offset' : +0.5,
        'ratio' : 1.1,
    },
    'Beat' : {
        'speed_rank_offset' : +0.7,
        'ratio' : 0.7,
    },
}

ALPHA, BETA = 1.14, 0.048


def r_prisec( tag, v1, v2, eml1, eml2 ):
   if tag in MOBILITY_PARAMS:
      return v1, round((v2*(eml1+eml2) - eml1*v1)/float(eml2))
   else:
      return v1, v2-v1

def fmt( t, half = False ):
   return str(int(round(t)))

def unstackvals( tag, text1, text2, eml1, eml2 ):
   o1, o2 = r_prisec(tag, float(text1), 0 if text2 == '' else float(text2), eml1, eml2)
   o1, o2 = fmt(o1), fmt(o2)
   if o2 == o1:
      return o1
   else:
      return {'pri': o1, 'sec': o2}

def dec_i( n ):
   if n <= 1:
      return 400.0
   else:
      return dec_i(n-1)/(ALPHA+BETA*(n-1))

def dec( f ):
   n = math.floor(f)
   q = 1.0*f - n
   n = int(n)
   return pow(dec_i(n), 1.0-q) * pow(dec_i(n+1), q)

def ls2vals( line, size ):
   stats = line_stats[line]

   # Modulate full speed based on the speed_ranke_offset stat
   fullspeed = dec( size + stats['speed_rank_offset'])

   # r ranges from 15% / 2 (size 6) to 15% * 2 (size 1)
   r = STD_R * pow(2, -R_MAG * ((size-1)-2.5) / 5)

   # Modulate ratio based on outfit
   r *= line_stats[line]['ratio']

   speed = fullspeed * (1.0-r)
   accel = fullspeed * r * PHYSICS_SPEED_DAMP

   turn = TURN_CT * fullspeed * pow(r/STD_R, AG_EXP)
   if 'turn' in stats:
      turn *= stats['turn']

   return {
      'speed' : speed,
      'accel' : accel,
      'turn' :  turn
   }

def get_line( name ):
   res = name.split(' ')[0]
   if res in line_stats:
      return res

out = lambda x: stdout.write(x+'\n')
err = lambda x, nnl = False: stderr.write(x+('' if nnl else '\n'))

def apply_ls( sub, o, additional = dict() ):
   if sub is not None:
      for k, v in additional.items():
         if k not in sub:
            sub[k] = v
      acc = []
      for d, k in o.nodes():
         k = k.lstrip('$')
         if k in sub and str(d[k]) != str(sub[k]):
            acc.append((k, d[k], sub[k]))
            d[k] = sub[k]
      return acc

def mk_subs( a, name = None ):
   sub = []
   for doubled in [False, True]:
      try:
         o = outfit(a)
      except:
         o = None

      if o is None:
         stderr.write('Invalid outfit "' + a + '" ignored\n')
         return None

      if name is None:
         name = o.name()

      line = get_line(name)
      if line is None:
         break

      o.stack(o if doubled else None)
      sub.append(ls2vals(line, o.size(doubled)))

   if not sub:
      return None

   return {k:(v1, sub[-1][k]) for k, v1 in sub[0].items()}

def psstr( t ):
   return str(t['pri']) + '/' + str(t['sec']) if isinstance(t, dict) else str(t)

def main( args ):
   outfits = []
   for a in args:
      sub = mk_subs(a)
      if sub is None:
         continue

      o = outfit(a)
      t = o.find('engine_limit')
      if isinstance(t, dict):
         eml1, eml2 = t['pri'], t['sec']
      else:
         eml1 = eml2 = t

      eml1, eml2 = float(eml1), float(eml2)

      if o.name() in ['Krain Remige Engine', "Za'lek Test Engine"]:
         sub = {k:fmt(v[0]) for k, v in sub.items()}
      elif o.name() == 'Krain Patagium Twin Engine':
         sub = {k:fmt(v[1]) for k, v in sub.items()}
      else:
         sub = {k:unstackvals(k, v[0], v[1], eml1, eml2) for k, v in sub.items()}

      if sub is not None:
         acc = apply_ls(sub, o)
         if acc is not None:
            err(o._filename.split('/')[-1]+': ', nnl = True)
            if acc:
               err(', '.join([i+':'+psstr(j)+'->'+psstr(k) for i, j, k in acc]))
               o.save()
            else:
               err('_')
   return 0

def gen_line( params ):
   import os
   outf_dir = os.path.join( os.path.dirname( __file__ ), '..', '..', 'dat', 'outfits')
   engine_dir = os.path.join( outf_dir, 'core_engine', 'small', 'beat_up_small_engine.xml')

   lin = params[0]
   try:
      params = list(map(float, params[1:]))
   except:
      err('Generation parameters should be floats: '+', '.join(map(repr, params[1:])))
      return 1

   if lin not in line_stats:
      line_stats[lin] = {'speed_rank_offset': 0, 'ratio': 1}

   line_stats[lin].update(zip(['speed_rank_offset', 'ratio', 'turn'], params))

   for i, s in enumerate(['Small', 'Medium', 'Large']):
      engine = engine_dir.replace('small', s.lower())
      o = outfit(engine, is_multi = True)

      if o is None:
         err('Beat up small engine, used as dummy, was not found!')
         return 1

      nam = lin + ' ' + s + ' Engine'
      o.set_name(nam)
      fil = nam2fil(nam + '.xml')

      sized_params = lambda n: {
         'mass':str(10*n),
         'fuel':str(int((n+4)*100*(2**int((n-1)/2)))),
      }
      additional = {k:(sized_params(2*i+1)[k], sized_params(2*i+1+1)[k]) for k in sized_params(2*1+1)}
      additional = {k:unstackvals(k, v[0], v[1], 1, 1) for k, v in additional.items()}
      additional['description'] = '"TODO"'
      additional['engine_limit'] = str(175*4**i)
      additional['price'] = str(12500*3**i)
      additional['energy_regen_malus'] = str(5*2**i)

      subs = {k:unstackvals(k, v[0], v[1], 1.0, 1.0) for k, v in mk_subs(engine, nam).items()}
      acc = apply_ls(subs, o, additional)
      o.save()
      err('<' + fil + '>')
   return 0

if __name__ == '__main__':
   import argparse

   parser = argparse.ArgumentParser(
      usage = " %(prog)s (-g line_name [speed_rank [ratio [turn]]]) | (filename ...) | -h",
      formatter_class = argparse.RawTextHelpFormatter,
      description = 'The changes made will be listed onto <stderr>: \"_\" means \"nothing\".',
      epilog = """Examples:
  Standard usage:
   > find dat/outfits/core_engine/ -name "*.xml" | ./utils/outfits/update_engines.py -f
  Generate a line called Krain with same params as Krain:
   > ./utils/outfits/update_engines.py -g Krain
  Generate a line called Melendez with same params as Melendez *but with speed_rank_offset = 0.5*:
   > ./utils/outfits/update_engines.py -g Melendez 0.5
  Generate a brand new line called Zednelem with with speed_rank_offset = 0.5 and default 1.0 ratio:
   > ./utils/outfits/update_engines.py -g Zednelem 0.5
  Generate a brand new line called Zednelem with with speed_rank_offset = 0.5 and 1.2 ratio:
   > ./utils/outfits/update_engines.py -g Zednelem 0.5 1.2
""")
   parser.add_argument('-f', '--files', action= 'store_true', help= 'read file list on stdin. Applies when no args.\nDoes not apply in generate mode.')
   parser.add_argument('-g', '--generate', action= 'store_true', help= 'line_name ex: "Melendez" or "Zednelem".')
   parser.add_argument('args', nargs= '*', help= 'An outfit with ".xml" extension, else will be silently ignored.\nIf not valid, will not even be printed out.')
   args = parser.parse_args()

   if args.generate:
      if args.args[4:]:
         err('Ignored: '+', '.join([repr(a) for a in args.args[4:]]))
         args.args = args.args[:4]
      exit(gen_line(args.args))
   else:
      if args.files or not args.args:
         args.args += [l.strip() for l in stdin.readlines()]
      exit(main([a for a in args.args if a.endswith('.xml')]))
