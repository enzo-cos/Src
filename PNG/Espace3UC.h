#ifndef ____ESPACE3UC____
#define ____ESPACE3UC____

class Espace3UC {

  public :
    int dx ;
    int dy ;
    unsigned char **p ;

  public :
    Espace3UC(int dx,int dy) ;
    ~Espace3UC(void) ;
    void init(unsigned char v) ;
    void init(unsigned char v1,unsigned char v2,unsigned char v3) ;
    void cherche(int x,int y,unsigned char *c) ;
    void sauve(unsigned char *c,int x,int y) ;
    long getUsedMemory(void);
    int getUsedHandles(void);
    int alloue(void);
} ;

#endif
