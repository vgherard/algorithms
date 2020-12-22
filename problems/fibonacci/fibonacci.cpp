// Compute the n-th term of the Fibonacci sequence

int fibonacci(int n) {
    if (n <= 1) return n;
    
    int f_m2 = 0;
    int f_m1 = 1;
    int f = 1;
    
    for (int k = 3; k <= n; k++){
        f_m2 = f_m1;
        f_m1 = f;
        f = f_m1 + f_m2;
    }

    return f;
}
