source = [
   configure_file(input: 'Config/cholmod.h.in', output: 'cholmod.h', format: 'cmake@', configuration: config),
   'Check/cholmod_check.c',                    # 'Check/cholmod_l_check.c',
   'Check/cholmod_read.c',                     # 'Check/cholmod_l_read.c',
   'Check/cholmod_write.c',                    # 'Check/cholmod_l_write.c',
   'Cholesky/cholmod_amd.c',                   # 'Cholesky/cholmod_l_amd.c',
   'Cholesky/cholmod_analyze.c',               # 'Cholesky/cholmod_l_analyze.c',
   'Cholesky/cholmod_colamd.c',                # 'Cholesky/cholmod_l_colamd.c',
   'Cholesky/cholmod_etree.c',                 # 'Cholesky/cholmod_l_etree.c',
   'Cholesky/cholmod_factorize.c',             # 'Cholesky/cholmod_l_factorize.c',
   'Cholesky/cholmod_postorder.c',             # 'Cholesky/cholmod_l_postorder.c',
   'Cholesky/cholmod_rcond.c',                 # 'Cholesky/cholmod_l_rcond.c',
   'Cholesky/cholmod_resymbol.c',              # 'Cholesky/cholmod_l_resymbol.c',
   'Cholesky/cholmod_rowcolcounts.c',          # 'Cholesky/cholmod_l_rowcolcounts.c',
   'Cholesky/cholmod_rowfac.c',                # 'Cholesky/cholmod_l_rowfac.c',
   'Cholesky/cholmod_solve.c',                 # 'Cholesky/cholmod_l_solve.c',
   'Cholesky/cholmod_spsolve.c',               # 'Cholesky/cholmod_l_spsolve.c',
   'MatrixOps/cholmod_drop.c',                 # 'MatrixOps/cholmod_l_drop.c',
   'MatrixOps/cholmod_horzcat.c',              # 'MatrixOps/cholmod_l_horzcat.c',
   'MatrixOps/cholmod_norm.c',                 # 'MatrixOps/cholmod_l_norm.c',
   'MatrixOps/cholmod_scale.c',                # 'MatrixOps/cholmod_l_scale.c',
   'MatrixOps/cholmod_sdmult.c',               # 'MatrixOps/cholmod_l_sdmult.c',
   'MatrixOps/cholmod_ssmult.c',               # 'MatrixOps/cholmod_l_ssmult.c',
   'MatrixOps/cholmod_submatrix.c',            # 'MatrixOps/cholmod_l_submatrix.c',
   'MatrixOps/cholmod_symmetry.c',             # 'MatrixOps/cholmod_l_symmetry.c',
   'MatrixOps/cholmod_vertcat.c',              # 'MatrixOps/cholmod_l_vertcat.c',
   'Modify/cholmod_rowadd.c',                  # 'Modify/cholmod_l_rowadd.c',
   'Modify/cholmod_rowdel.c',                  # 'Modify/cholmod_l_rowdel.c',
   'Modify/cholmod_updown.c',                  # 'Modify/cholmod_l_updown.c',
   'Utility/cholmod_aat.c',                     # 'Utility/cholmod_l_aat.c',
   'Utility/cholmod_add.c',                     # 'Utility/cholmod_l_add.c',
   'Utility/cholmod_add_size_t.c',              # 'Utility/cholmod_l_add_size_t.c',
   'Utility/cholmod_alloc_factor.c',            # 'Utility/cholmod_l_alloc_factor.c',
   'Utility/cholmod_alloc_work.c',              # 'Utility/cholmod_l_alloc_work.c',
   'Utility/cholmod_allocate_dense.c',          # 'Utility/cholmod_l_allocate_dense.c',
   'Utility/cholmod_allocate_factor.c',         # 'Utility/cholmod_l_allocate_factor.c',
   'Utility/cholmod_allocate_sparse.c',         # 'Utility/cholmod_l_allocate_sparse.c',
   'Utility/cholmod_allocate_triplet.c',        # 'Utility/cholmod_l_allocate_triplet.c',
   'Utility/cholmod_allocate_work.c',           # 'Utility/cholmod_l_allocate_work.c',
   'Utility/cholmod_band.c',                    # 'Utility/cholmod_l_band.c',
   'Utility/cholmod_band_nnz.c',                # 'Utility/cholmod_l_band_nnz.c',
   'Utility/cholmod_calloc.c',                  # 'Utility/cholmod_l_calloc.c',
   'Utility/cholmod_change_factor.c',           # 'Utility/cholmod_l_change_factor.c',
   'Utility/cholmod_clear_flag.c',              # 'Utility/cholmod_l_clear_flag.c',
   'Utility/cholmod_copy.c',                    # 'Utility/cholmod_l_copy.c',
   'Utility/cholmod_copy_dense.c',              # 'Utility/cholmod_l_copy_dense.c',
   'Utility/cholmod_copy_dense2.c',             # 'Utility/cholmod_l_copy_dense2.c',
   'Utility/cholmod_copy_factor.c',             # 'Utility/cholmod_l_copy_factor.c',
   'Utility/cholmod_copy_sparse.c',             # 'Utility/cholmod_l_copy_sparse.c',
   'Utility/cholmod_copy_triplet.c',            # 'Utility/cholmod_l_copy_triplet.c',
   'Utility/cholmod_cumsum.c',                  # 'Utility/cholmod_l_cumsum.c',
   'Utility/cholmod_dbound.c',                  # 'Utility/cholmod_l_dbound.c',
   'Utility/cholmod_defaults.c',                # 'Utility/cholmod_l_defaults.c',
   'Utility/cholmod_dense_nnz.c',               # 'Utility/cholmod_l_dense_nnz.c',
   'Utility/cholmod_dense_to_sparse.c',         # 'Utility/cholmod_l_dense_to_sparse.c',
   'Utility/cholmod_divcomplex.c',              # 'Utility/cholmod_l_divcomplex.c',
   'Utility/cholmod_ensure_dense.c',            # 'Utility/cholmod_l_ensure_dense.c',
   'Utility/cholmod_error.c',                   # 'Utility/cholmod_l_error.c',
   'Utility/cholmod_eye.c',                     # 'Utility/cholmod_l_eye.c',
   'Utility/cholmod_factor_to_sparse.c',        # 'Utility/cholmod_l_factor_to_sparse.c',
   'Utility/cholmod_finish.c',                  # 'Utility/cholmod_l_finish.c',
   'Utility/cholmod_free.c',                    # 'Utility/cholmod_l_free.c',
   'Utility/cholmod_free_dense.c',              # 'Utility/cholmod_l_free_dense.c',
   'Utility/cholmod_free_factor.c',             # 'Utility/cholmod_l_free_factor.c',
   'Utility/cholmod_free_sparse.c',             # 'Utility/cholmod_l_free_sparse.c',
   'Utility/cholmod_free_triplet.c',            # 'Utility/cholmod_l_free_triplet.c',
   'Utility/cholmod_free_work.c',               # 'Utility/cholmod_l_free_work.c',
   'Utility/cholmod_hypot.c',                   # 'Utility/cholmod_l_hypot.c',
   'Utility/cholmod_malloc.c',                  # 'Utility/cholmod_l_malloc.c',
   'Utility/cholmod_maxrank.c',                 # 'Utility/cholmod_l_maxrank.c',
   'Utility/cholmod_memdebug.c',
   'Utility/cholmod_mult_size_t.c',             # 'Utility/cholmod_l_mult_size_t.c',
   'Utility/cholmod_mult_uint64_t.c',
   'Utility/cholmod_nnz.c',                     # 'Utility/cholmod_l_nnz.c',
   'Utility/cholmod_ones.c',                    # 'Utility/cholmod_l_ones.c',
   'Utility/cholmod_pack_factor.c',             # 'Utility/cholmod_l_pack_factor.c',
   'Utility/cholmod_ptranspose.c',              # 'Utility/cholmod_l_ptranspose.c',
   'Utility/cholmod_realloc.c',                 # 'Utility/cholmod_l_realloc.c',
   'Utility/cholmod_realloc_multiple.c',        # 'Utility/cholmod_l_realloc_multiple.c',
   'Utility/cholmod_reallocate_column.c',       # 'Utility/cholmod_l_reallocate_column.c',
   'Utility/cholmod_reallocate_factor.c',       # 'Utility/cholmod_l_reallocate_factor.c',
   'Utility/cholmod_reallocate_sparse.c',       # 'Utility/cholmod_l_reallocate_sparse.c',
   'Utility/cholmod_reallocate_triplet.c',      # 'Utility/cholmod_l_reallocate_triplet.c',
   'Utility/cholmod_sbound.c',                  # 'Utility/cholmod_l_sbound.c',
   'Utility/cholmod_score_comp.c',              # 'Utility/cholmod_l_score_comp.c',
   'Utility/cholmod_set_empty.c',               # 'Utility/cholmod_l_set_empty.c',
   'Utility/cholmod_sort.c',                    # 'Utility/cholmod_l_sort.c',
   'Utility/cholmod_sparse_to_dense.c',         # 'Utility/cholmod_l_sparse_to_dense.c',
   'Utility/cholmod_sparse_to_triplet.c',       # 'Utility/cholmod_l_sparse_to_triplet.c',
   'Utility/cholmod_speye.c',                   # 'Utility/cholmod_l_speye.c',
   'Utility/cholmod_spzeros.c',                 # 'Utility/cholmod_l_spzeros.c',
   'Utility/cholmod_start.c',                   # 'Utility/cholmod_l_start.c',
   'Utility/cholmod_transpose.c',               # 'Utility/cholmod_l_transpose.c',
   'Utility/cholmod_transpose_sym.c',           # 'Utility/cholmod_l_transpose_sym.c',
   'Utility/cholmod_transpose_unsym.c',         # 'Utility/cholmod_l_transpose_unsym.c',
   'Utility/cholmod_triplet_to_sparse.c',       # 'Utility/cholmod_l_triplet_to_sparse.c',
   'Utility/cholmod_version.c',                 # 'Utility/cholmod_l_version.c',
   'Utility/cholmod_xtype.c',                   # 'Utility/cholmod_l_xtype.c',
   'Utility/cholmod_zeros.c',                   # 'Utility/cholmod_l_zeros.c',


   # Naev does not need Partition/* or Supernodal/*
]

include = include_directories([
   'Include',
   '../AMD/Include',
   '../COLAMD/Include',
   '../SuiteSparse_config',
])

cc = meson.get_compiler('c')
system_deps = [
   cc.find_library('m', required : false)
]

libcholmod = static_library(
   'cholmod',
   source,
   c_args: ['-DNCAMD', '-DNPARTITION', '-DNSUPERNODAL'],
   dependencies: system_deps,
   include_directories: include
)

CHOLMOD_dep = declare_dependency(
   link_with: libcholmod,
   include_directories: include,
   compile_args: ['-DNCAMD', '-DNPARTITION', '-DNSUPERNODAL'],
   link_args: ['-DNCAMD', '-DNPARTITION', '-DNSUPERNODAL'],
   dependencies: system_deps
)
