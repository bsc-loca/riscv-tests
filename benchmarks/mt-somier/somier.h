
extern void init_forloop_boundries (int cid,int nc, int dim );
extern void acceleration(int cid, int nc, int n, data_t (*A)[n][n][n], data_t (*F)[n][n][n], data_t M);
extern void velocities(int cid, int nc, int n, data_t (*V)[n][n][n], data_t (*A)[n][n][n], data_t dt);
extern void positions(int cid, int nc, int n, data_t (*X)[n][n][n], data_t (*V)[n][n][n], data_t dt);
extern void compute_stats(int cid, int nc, int n, data_t (*X)[n][n][n], data_t Xcenter[3]);
extern void force_contribution(int cid, int nc, int n, data_t (*X)[n][n][n], data_t (*F)[n][n][n],
                   int i, int j, int k, int neig_i, int neig_j, int neig_k);
extern void compute_forces(int cid, int nc, int n, data_t (*X)[n][n][n], data_t (*F)[n][n][n]);

extern void compute_stats_pre(int cid, int nc, int n, data_t (*X)[n][n][n]);


extern data_t M;
extern data_t dt;
extern data_t spring_K;
