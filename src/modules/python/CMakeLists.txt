install(FILES
  pbs/__init__.py
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/python/altair/pbs
)
install(FILES
  ${CMAKE_BINARY_DIR}/src/lib/Libpython/pbs_ifl.py
  pbs/v1/__init__.py
  pbs/v1/_attr_types.py
  pbs/v1/_base_types.py
  pbs/v1/_exc_types.py
  pbs/v1/_export_types.py
  pbs/v1/_svr_types.py
  pbs/v1/_pmi_types.py
  pbs/v1/_pmi_sgi.py
  pbs/v1/_pmi_cray.py
  pbs/v1/_pmi_none.py
  pbs/v1/_pmi_utils.py
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/python/altair/pbs/v1
)
install(FILES
  pbs_hooks/PBS_power.HK
  pbs_hooks/PBS_power.PY
  pbs_hooks/PBS_power.CF
  pbs_hooks/PBS_alps_inventory_check.HK
  pbs_hooks/PBS_alps_inventory_check.PY
  pbs_hooks/PBS_xeon_phi_provision.HK
  pbs_hooks/PBS_xeon_phi_provision.PY
  pbs_hooks/PBS_cray_atom.HK
  pbs_hooks/PBS_cray_atom.PY
  pbs_hooks/PBS_cray_atom.CF
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/python/altair/pbs_hooks
)