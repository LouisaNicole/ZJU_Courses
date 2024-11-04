#include<bits/stdc++.h>  // Include the entire standard library

#include <iostream>  // Include the input/output stream library
#include <chrono>    // Include the chrono library for time measurement

using namespace std;

typedef long long ll;  // Define the "ll" type as a long long integer
const int MAX_LEN = 1000000;  // Define the maximum length constant
const int PRIMITIVE_ROOT = 3;  // Define the primitive root constant

const ll MOD_1 = 998244353;    // Define the first modulus
const ll MOD_2 = 1004535809;   // Define the second modulus
const ll MOD_3 = 469762049;    // Define the third modulus

int length = 1;  // Initialize the length variable
ll omega, omega_inverse;  // Declare variables for omega and its inverse
ll B[MAX_LEN + 5], R[MAX_LEN + 5], O[MAX_LEN + 5];  // Declare arrays B, R, and O
ll c1[MAX_LEN + 5], c2[MAX_LEN + 5], c3[MAX_LEN + 5];  // Declare arrays c1, c2, and c3
ll x[MAX_LEN + 5], y[MAX_LEN + 5];  // Declare arrays x and y

ll mod_exponentiation(ll base, ll exponent, ll mod) {  // Function to perform modular exponentiation
    if (exponent == 0) return 1;  // Base case: exponent is 0, return 1
    ll result = mod_exponentiation(base, exponent / 2, mod);  // Recursively calculate base^(exponent/2) modulo mod
    result = (result * result) % mod;  // Square the result and take modulo mod
    if (exponent % 2 == 1) result = (result * base) % mod;  // If exponent is odd, multiply result by base and take modulo mod
    return result;  // Return the final result
}

void change_order(ll *array, int length) {  // Function to change the order of elements in the array
    for (int i = 1, j = length / 2, k; i < length - 1; i++) {
        if (i < j) swap(array[i], array[j]);  // Swap the elements at indices i and j
        k = length / 2;
        while (j >= k) {  // Calculate the new value of j
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

void ntt(ll *array, int length, int inverse, ll mod) {  // Function to perform number-theoretic transform (NTT)
    change_order(array, length);  // Change the order of elements in the array
    for (int i = 2; i <= length; i <<= 1) {  // Iterate over the array in powers of 2
        if (inverse == 1) omega = mod_exponentiation(PRIMITIVE_ROOT, (mod - 1) / i, mod);  // Calculate the Nth root of unity
        else omega = mod_exponentiation(PRIMITIVE_ROOT, mod - 1 - (mod - 1) / i, mod);  // Calculate the inverse Nth root of unity
        for (int j = 0; j < length; j += i) {  // Iterate over the array in steps of i
            ll w = 1;
            for (int k = j; k < j + i / 2; k++, w = (w * omega) % mod) {  // Perform butterfly operations
                ll t = array[k], u = (w * array[k + i / 2]) % mod;
                array[k] = (t + u) % mod;
                array[k + i / 2] = (t - u + mod) % mod;
            }
        }
    }
    if (inverse == -1) {  // If inverse is -1, perform inverse NTT
        ll inverse_length = mod_exponentiation(length, mod - 2, mod);  // Calculate the inverse length
        for (int i = 0; i < length; i++) array[i] = (array[i] * inverse_length) % mod;  // Scale the elements by the inverse length
    }
}

void mtt(ll *a, ll *b, ll *result, ll mod) {
    for (int i = 0; i < length; i++) {
        x[i] = a[i];
        y[i] = b[i];
    }
    ntt(x, length, 1, mod);
    ntt(y, length, 1, mod);
    for (int i = 0; i < length; i++) {
        result[i] = (x[i] * y[i]) % mod;
    }
    ntt(result, length, -1, mod);
}

int main()
{
    ll trees = 0;
    int n = 500, MOD=1000000007;
    double time;
    // cin >> N;
    ios::sync_with_stdio(false);
    ofstream file;
    file.open("../black_red_mtt.txt");
    for(int N = 1; N <= 500; N++) {
        
        int BH = (int)(log2(N + 1));
        memset(B,0,sizeof(B));memset(R,0,sizeof(R));memset(O,0,sizeof(O));
        memset(c1,0,sizeof(c1));memset(c2,0,sizeof(c2));memset(c3,0,sizeof(c3));
        memset(x,0,sizeof(x));memset(y,0,sizeof(y)); omega=0; omega_inverse=0;
        auto start = chrono::high_resolution_clock::now();
        trees = 0;
        length = 1;
        B[0] = 1;
        R[1] = 1;
        int num = 1;
        // Perform calculations for each height
        for (int h = 1; h <= BH; h++) {
            while (length < 2 * num + 2)
                length <<= 1;
            
            // Calculate B and O polynomials
            for (int i = 0; i <= num; i++) {
                B[i] = (B[i] + R[i]) % MOD;
                if (!i) O[i] = 0;
                O[i + 1] = B[i];
            }
            
            // Perform Number Theoretic Transform (NTT) for three different moduli
            mtt(B, O, c1, MOD_1);
            mtt(B, O, c2, MOD_2);
            mtt(B, O, c3, MOD_3);
            
            // Perform modular arithmetic for the three moduli
            ll MOD_12 = MOD_1 * MOD_2;
            ll ny1 = mod_exponentiation(MOD_1, MOD_2 - 2, MOD_2);
            ll ny12 = mod_exponentiation(MOD_12 % MOD_3, MOD_3 - 2, MOD_3);
            
            for (int i = 0; i < length; i++) {
                c1[i] = (((c2[i] - c1[i]) % MOD_2 + MOD_2) % MOD_2 * ny1 % MOD_2 * MOD_1 + c1[i]) % MOD_12;
                c3[i] = (((c3[i] - c1[i]) % MOD_3 + MOD_3) % MOD_3 * ny12 % MOD_3 * (MOD_12 % MOD) % MOD + c1[i] % MOD) % MOD;
            }
            
            // Update B array
            for (int i = 0; i < 2 * num + 2; i++)
                B[i] = c3[i];
            
            num = (2 * num + 1 > 500) ? 1000 : (2 * num + 1);
            
            while (length < 2 * num + 2)
                length <<= 1;
            
            // Calculate B and O polynomials
            for (int i = 0; i <= num; i++) {
                if (!i) O[i] = 0;
                O[i + 1] = B[i];
            }
            
            // Perform Number Theoretic Transform (NTT) for three different moduli
            mtt(B, O, c1, MOD_1);
            mtt(B, O, c2, MOD_2);
            mtt(B, O, c3, MOD_3);
            
            // Perform modular arithmetic for the three moduli
            MOD_12 = MOD_1 * MOD_2;
            ny1 = mod_exponentiation(MOD_1, MOD_2 - 2, MOD_2);
            ny12 = mod_exponentiation(MOD_12 % MOD_3, MOD_3 - 2, MOD_3);
            
            for (int i = 0; i < length; i++) {
                c1[i] = (((c2[i] - c1[i]) % MOD_2 + MOD_2) % MOD_2 * ny1 % MOD_2 * MOD_1 + c1[i]) % MOD_12;
                c3[i] = (((c3[i] - c1[i]) % MOD_3 + MOD_3) % MOD_3 * ny12 % MOD_3 * (MOD_12 % MOD) % MOD + c1[i] % MOD) % MOD;
            }
            
            // Update R array
            for (int i = 0; i < 2 * num + 2; i++)
                R[i] = c3[i];
            
            num = (2 * num + 1 > 500) ? 500 : (2 * num + 1);
            
            trees = (trees + B[N]) % MOD;
        }
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        
        // Write the results to the output file
        file << "The number of trees=" << trees << " with " << N << "nodes. " << "Cost is : " << duration.count() << "s." << endl;
    }
    file.close();
	return 0;
}