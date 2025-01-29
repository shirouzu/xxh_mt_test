# xxh3 multi-threaded performance test

## Overview
Displays the total speed when each thread calculates 1GB buffer(=THR_BUFSZ) of xxh3/AVX2 10 times(=COUNT).

## Results
Xeon w5-3425 (12core/24threads) + X13SWA-TF + 8ch memory + 128GB(DDR5-4800 16GB x8) + Win10 Pro Workstation

```
Prepare buffer...end
Theads=24: 136.44GiB/s (1759ms for 240GiB)
Theads=23: 135.93GiB/s (1692ms for 230GiB)
Theads=22: 133.66GiB/s (1646ms for 220GiB)
Theads=21: 129.87GiB/s (1617ms for 210GiB)
Theads=20: 128.29GiB/s (1559ms for 200GiB)
Theads=19: 124.59GiB/s (1525ms for 190GiB)
Theads=18: 117.80GiB/s (1528ms for 180GiB)
Theads=17: 117.57GiB/s (1446ms for 170GiB)
Theads=16: 112.68GiB/s (1420ms for 160GiB)
Theads=15: 110.05GiB/s (1363ms for 150GiB)
Theads=14: 105.90GiB/s (1322ms for 140GiB)
Theads=13: 103.75GiB/s (1253ms for 130GiB)
Theads=12: 96.23GiB/s (1247ms for 120GiB)
Theads=11: 91.82GiB/s (1198ms for 110GiB)
Theads=10: 92.94GiB/s (1076ms for 100GiB)
Theads=9: 78.88GiB/s (1141ms for 90GiB)
Theads=8: 81.14GiB/s (986ms for 80GiB)
Theads=7: 73.76GiB/s (949ms for 70GiB)
Theads=6: 61.66GiB/s (973ms for 60GiB)
Theads=5: 55.68GiB/s (898ms for 50GiB)
Theads=4: 46.78GiB/s (855ms for 40GiB)
Theads=3: 35.80GiB/s (838ms for 30GiB)
Theads=2: 25.74GiB/s (777ms for 20GiB)
Theads=1: 13.16GiB/s (760ms for 10GiB)
```
