for(int i=1;i<=n;i++){
    EnQ(Q,0);
    for(int j=1;j<=i+2;j++){
        s=DeQ(Q);
        e=Front(Q);
        EnQ(Q,s+e);
    }
}

0 1 1 0 1 2 1 0 1 3 3 1 0 ...