本项目是用C++手搓LevelDb数据库，旨在从零实现一个类似 LevelDB 的 LSM-Tree
存储引擎，包含 MemTable、WAL（预写日志）、SSTable（不可变有序文件）与简单的
Compaction（压缩合并）机制。该项目适合学习底层数据库系统架构，理解持久化、日志与索引
实现原理。

目前支持基本的 KV 操作接口（put/get/delete），后续将逐步加入：
- 崩溃恢复（WAL Replay）
- 多层 Compaction 策略
- 简易缓存（如 LRU）
- 可视化调试工具

目标是写出一份结构清晰、逻辑完整、注释丰富的“教学级”数据库实现，既能用于学习，又能作为
目展示。

计划用时两周

项目构建
my-leveldb-clone/
├── CMakeLists.txt          # 编译配置
├── README.md               # 项目说明
├── LICENSE                 # 开源许可证（如 MIT）
├── .gitignore              # 忽略构建和中间文件
│
├── include/                # 所有头文件（*.hpp）
│   ├── db.hpp              # 对外暴露的主接口（put/get/delete）
│   ├── memtable.hpp        # 内存表结构（跳表/map）
│   ├── log.hpp             # 写前日志模块接口
│   ├── sstable.hpp         # SSTable 文件格式接口
│   ├── compaction.hpp      # Compaction 合并模块接口
│   ├── lru_cache.hpp       # 缓存模块接口（可选）
│   └── util.hpp            # 辅助函数和通用工具
│
├── src/                    # 所有实现文件（*.cpp）
│   ├── main.cpp            # 主程序入口（调试/演示）
│   ├── db.cpp              # 数据库主接口的实现
│   ├── memtable.cpp        # 内存表逻辑
│   ├── log.cpp             # 写前日志逻辑
│   ├── sstable.cpp         # 写入/读取 SSTable 文件
│   ├── compaction.cpp      # 实现 sstable 合并
│   ├── lru_cache.cpp       # LRU 缓存实现（可选）
│   └── util.cpp            # 通用函数实现
│
├── test/                   # 单元测试（可用 GoogleTest/Catch2）
│   ├── test_db.cpp         # 测试 put/get/delete 功能
│   ├── test_memtable.cpp   # 测试内存表模块
│   ├── test_wal.cpp        # 测试 WAL 写入恢复
│   └── ...
│
├── data/                   # 程序运行中生成的数据文件
│   ├── wal.log             # 写前日志文件
│   ├── sstable-0001.sst    # SSTable 文件
│   └── ...                 # 后续更多文件
│
├── build/                  # CMake 生成的构建目录（不要手动编辑）
└── docs/                   # 项目设计文档（可选）
    ├── architecture.md     # 系统架构说明
    └── sstable_format.md   # SSTable 格式文档（方便后续调试）
    

🧱 项目构建结构详解

my-leveldb-clone/

这是项目的根目录，包含构建配置、源码、测试、文档、数据文件等全部内容。


🔧 根目录文件
    •    CMakeLists.txt
用于配置项目的构建过程（使用 CMake 工具）。定义源文件路径、编译参数、依赖库等，是项目的“构建说明书”。
    •    README.md
项目说明文档。介绍项目背景、功能、使用方法、构建步骤等。
    •    LICENSE
项目许可证文件，推荐使用 MIT、Apache 2.0 等开源协议。
    •    .gitignore
Git 忽略文件。定义不应该提交到 Git 仓库的文件，如临时文件、构建产物、数据库文件等。

⸻

📁 include/ — 头文件目录

放置所有模块的接口定义（.hpp），用于声明类、结构体和函数。
    •    db.hpp
数据库主入口类的声明，提供对外的 put / get / delete 接口。
    •    memtable.hpp
内存表模块接口。定义用于暂存写入数据的结构，通常使用跳表（SkipList）或 std::map 实现。
    •    wal.hpp
Write-Ahead Log 模块接口。定义用于持久化写操作的日志系统，支持宕机恢复。
    •    sstable.hpp
SSTable（Sorted String Table）模块接口。负责将内存表写入磁盘，并支持后续读取。
    •    compaction.hpp
定义数据压缩合并的接口。用于整理多个 SSTable，删除重复键、提升读取效率。
    •    lru_cache.hpp (可选)
缓存模块接口。实现 LRU 缓存策略，减少磁盘访问次数，提高性能。
    •    util.hpp
通用工具函数，如序列化、校验和、日志辅助等。

⸻

📁 src/ — 源码实现目录

存放各模块的实际实现文件（.cpp），与 include/ 中的 .hpp 一一对应。
    •    main.cpp
程序入口，用于简单演示数据库功能或提供命令行交互接口。
    •    db.cpp
实现数据库主接口类。调用 WAL、MemTable、SSTable 等子模块，完成完整的 KV 操作。
    •    memtable.cpp
实现内存表逻辑。支持插入、查找、删除、范围遍历等操作。
    •    wal.cpp
实现预写日志功能。保证写操作的持久性，支持宕机后恢复。
    •    sstable.cpp
实现 SSTable 的写入与读取逻辑，包括索引构建、文件格式管理等。
    •    compaction.cpp
实现 Compaction 操作：合并多个旧的 SSTable 文件，消除冗余数据。
    •    lru_cache.cpp (可选)
实现 LRU 缓存算法，用于加速读取热点数据。
    •    util.cpp
实现项目中常用的辅助函数，如字符串处理、校验计算、文件操作等。

⸻

📁 test/ — 单元测试目录

用于模块测试和功能验证，推荐使用 Google Test 或 Catch2 测试框架。
    •    test_db.cpp
测试数据库主接口是否正常工作（如 put、get、delete 的正确性）。
    •    test_memtable.cpp
测试内存表插入、查找、删除是否正确。
    •    test_wal.cpp
测试写前日志能否正确写入并在崩溃后恢复数据。
    •    ...
可添加更多模块的单元测试文件，如 SSTable、Compaction、LRU 缓存等。

⸻

📁 data/ — 数据文件目录

用于程序运行时生成的文件数据，方便调试和查看存储效果。
    •    wal.log
当前正在写入的预写日志文件。
    •    sstable-0001.sst
某次 flush 后生成的 SSTable 文件。通常是只读的、有序的文件格式。
    •    ...
后续可能生成更多日志、sst 文件，文件名通常有编号。

⸻

📁 build/ — 构建产物目录

CMake 构建时生成的中间文件和可执行文件。这个目录由 CMake 自动创建，不建议手动编辑或提交到 Git。

⸻

📁 docs/ — 设计文档目录 (可选，但推荐)

用于记录项目设计过程、格式规范、优化思路等，便于维护和学习。
    •    architecture.md
系统整体架构说明文档，解释各模块如何协作（如数据写入路径、读取流程、恢复流程等）。
    •    sstable_format.md
SSTable 文件结构文档，包括 block 格式、索引位置、CRC 校验、footer 等定义。


