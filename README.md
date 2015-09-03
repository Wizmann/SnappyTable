# SnappyTable
An experiment of using snappy compression to optimize the resource utilization for the variable-length data in a memory-based database.

## Performance & Compression Rate

The input data is a 6.5G txt file of json string. And the test runs on a "Intel(R) Xeon(R) CPU E5645" machine with **one single thread**. That is, the performance could be much better if you take the advantage of multi-thread on multi cores.

| Data source | Data size | QPS (1 core) |
| --- | --- | --- |
| Original  | 6.5G | - | - |
| Deduplicated | 3.1G | - | - |
| Deduplicate + Snappy + Compress with no batching | 0.7G | 135K |
| Deduplicate + Snappy + Compress with 4k block | 0.58G | 124K |
| Deduplicate + Snappy + Compress with 8k block | 0.51G | 99K |
| Deduplicate + Snappy + Compress with 16k block | 0.34G | 70K |
| Deduplicate + Snappy + Compress with 32k block | 0.28G | 40K |
| Deduplicate + Snappy + Compress with 64k block | 0.28G | 22K |
