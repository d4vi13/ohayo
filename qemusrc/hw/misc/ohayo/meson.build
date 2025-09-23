ohayo_ss = ss.source_set()
ohayo_ss.add(files(
  'ohayo.c',
  'mmio.c',
  'irq.c',
))

system_ss.add_all(when: 'CONFIG_OHAYO', if_true: ohayo_ss)

