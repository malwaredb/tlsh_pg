#### TLSH_PG
This project adds an extension to the [Postgres](https://www.postgresql.org/) database server to allow querying data by TLSH similarity. TLSH is the [Trend Micro Locality Sensitive Hash](https://github.com/trendmicro/tlsh).

#### Compiling:
1. Install pre-requisites: CMake, Postgres server dev packages. On Ubuntu/Debian, this can be done by running `sudo apt-get install cmake postgresql-server-dev-12` where 12 indicates the version of Postgres you're using.
2. `git clone --recursive https://github.com/malwaredb/tlsh_pg.git`
3. `cd tlsh_pg`
4. Build TLSH, since it generates a needed header file.
    1. `cd tlsh`
    2. `./make.sh`
5. `mkdir build`
6. `cd build`
7. `cmake .. -DCMAKE_BUILD_TYPE=Release`
8. `make`
9. Installation & testing:
   1. Copy the resulting library to the Postgres `lib` directory, which is shown by running `pg_config --pkglibdir`.
   2. As the Postgres user, run `psql DBNAME`, where you'll load the libary for the database schema you wish to use it with. This is done per-schema, as a privileged user.
   3. At the psql prompt, run `CREATE OR REPLACE FUNCTION tlsh_compare(TEXT, TEXT) RETURNS INTEGER AS 'tlsh_psql.so', 'pg_tlsh_compare' LANGUAGE 'c';`.
   4. Test by running `select tlsh_compare('T14814B643D364FEBFD624EAF8998AB8D5D4A5B0022BF00E5B65420EB704CE9D067543ED','T18784FA0392966E7FC9D6EFF8168BA4E5D562FC504BF0093B75404E3518CA9D0AB393E8');`. The result should be 233.