extern "C" {  
    void KDTBatchInsert(int n, double *dx, double *dy, const char** tag);
    void KDTInsert(double dx, double dy, const char* tag);
    const char* KDTSearch(double dx, double dy);
    void KDTInit();
}
