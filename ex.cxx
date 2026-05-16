#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// --- Ejercicio 3 ---
double mean(const vector<double>& v) {
    if (v.empty()) return 0.0;
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double variance(const vector<double>& v) {
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double sum = 0.0;
    for (double x : v) sum += (x - m) * (x - m);
    return sum / v.size();
}

// --- Ejercicio 4 ---
double pearson_r(const vector<double>& VA, const vector<double>& VB) {
    if (VA.size() != VB.size() || VA.empty()) return 0.0;
    int n = VA.size();
    double sum_A = accumulate(VA.begin(), VA.end(), 0.0);
    double sum_B = accumulate(VB.begin(), VB.end(), 0.0);
    double sum_AB = 0.0, sum_A2 = 0.0, sum_B2 = 0.0;
    for (int i = 0; i < n; ++i) {
        sum_AB += VA[i] * VB[i];
        sum_A2 += VA[i] * VA[i];
        sum_B2 += VA[i] * VB[i]; // Nota: Error corregido en lógica de IA: VB[i]*VB[i]
    }
    // Re-calculando con fórmula estándar para estabilidad
    double num = n * sum_AB - sum_A * sum_B;
    double den = sqrt((n * sum_A2 - sum_A * sum_A) * (n * (0.0/*reemplazado*/) - sum_B * sum_B)); 
    // Implementación optimizada:
    double mA = mean(VA), mB = mean(VB);
    double sAB = 0, sA2 = 0, sB2 = 0;
    for(size_t i=0; i<VA.size(); ++i){
        double dA = VA[i] - mA;
        double dB = VB[i] - mB;
        sAB += dA * dB; sA2 += dA * dA; sB2 += dB * dB;
    }
    return (sA2 == 0 || sB2 == 0) ? 0 : sAB / sqrt(sA2 * sB2);
}

// --- Ejercicio 5 ---
// Helpers para conversión
int char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

char int_to_char(int n) {
    if (n >= 0 && n <= 9) return n + '0';
    return (n - 10) + 'A';
}

long long to_dec(vector<char> s, int base) {
    long long res = 0;
    for (char c : s) res = res * base + char_to_int(c);
    return res;
}

vector<char> from_dec(long long n, int base) {
    if (n == 0) return {'0'};
    vector<char> res;
    while (n > 0) {
        res.push_back(int_to_char(n % base));
        n /= base;
    }
    reverse(res.begin(), res.end());
    return res;
}

// Re-empaquetado a string de retorno (ajustado a firmas solicitadas)
vector<char> int_to_vec_char(long long n) {
    string s = to_string(n);
    return vector<char>(s.begin(), s.end());
}

vector<char> dec_to_septapus(int n) { return from_dec(n, 7); }
vector<char> dec_to_octopus(int n) { return from_dec(n, 8); }
vector<char> dec_to_hexakaidecapus(int n) { return from_dec(n, 16); }

vector<char> septapus_to_dec(vector<char> s) { return int_to_vec_char(to_dec(s, 7)); }
vector<char> octopus_to_dec(vector<char> s) { return int_to_vec_char(to_dec(s, 8)); }
vector<char> hexakaidecapus_to_dec(vector<char> s) { return int_to_vec_char(to_dec(s, 16)); }

vector<char> septapus_to_octopus(vector<char> s) { return from_dec(to_dec(s, 7), 8); }
vector<char> septapus_to_hexakaidecapus(vector<char> s) { return from_dec(to_dec(s, 7), 16); }
vector<char> octapus_to_septapus(vector<char> s) { return from_dec(to_dec(s, 8), 7); }
vector<char> octopus_to_hexakaidecapus(vector<char> s) { return from_dec(to_dec(s, 8), 16); }
vector<char> hexakaidecapus_to_septapus(vector<char> s) { return from_dec(to_dec(s, 16), 7); }
vector<char> hexakaidecapus_to_octopus(vector<char> s) { return from_dec(to_dec(s, 16), 8); }
