int max(int a, int b, char c) {
    int result = a;
    if (a < b) {
        result = b;
    }
    return result;
}

int factorial(int n) {
    int result = 1;
    while (n > 0) {
        result = result * n;
        n--;
    }
    return result + 1;
}

int main() {
    int x = 10;
    int y = 20;
    int z;

    z = max(x, y, 'c');

    int n = 5;
    int fact;

    fact = factorial(n);   

    return 0;
}
