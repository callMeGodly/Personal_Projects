#include <vector>
#include <cmath>
#include <complex>

#define cd std::complex<double>

void FFT(std::vector<cd> & input, bool invert){

    int len = input.size();

    if(len==1) return;

    std::vector<cd> even, odd;
    for(int i = 0; i < len; ++i){
        if(i % 2 == 0) even.push_back(input[i]);
        else odd.push_back(input[i]);
    }

    FFT(even, invert);
    FFT(odd, invert);
    
    double ang = 2 * M_PI / len * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));

    for(double i = 0; i < len/2; ++i){
        input[i] = even[i] + w*odd[i];
        input[i + len/2] = even[i] - w*odd[i];
        w *= wn;
        if(invert){
            input[i] /= 2;
            input[i + len/2] /= 2;
        }
    }
}

std::vector<int> convert(std::vector<int> input, int l){

    std::vector<int> retval;
    for(int i = input.size()/2; i < input.size()/2 + l*2 - 1; ++i){
        retval.push_back(input[i]);
    }
    return retval;
}

std::vector<int> poly_multiplication(std::vector<int> const& a, std::vector<int> const& b){

    int l = a.size();
    
    std::vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);

    for(int i = 0; i < n; ++i) fa[i] *= fb[i];

    FFT(fa, true);

    std::vector<int> result(n);
    for (int i = 0; i < n; i++){
        result.push_back(round(fa[i].real()));
    }

    result = convert(result, l);

    return result;
}