#ifndef TRINARY
#define TRINARY

#include <array>
#include <cmath>

template <size_t seq_size>

class trinary {
 private:
  std::pair<unsigned char, unsigned char> sum(unsigned char a,
                                              unsigned char b) {
    return ((a + b == 0)   ? (std::pair<unsigned char, unsigned char>){0, 0}
            : (a + b == 1) ? (std::pair<unsigned char, unsigned char>){1, 0}
            : (a + b == 3) ? (std::pair<unsigned char, unsigned char>){0, 0}
            : (a == 1 && a + b == 2)
                ? (std::pair<unsigned char, unsigned char>){2, 1}
            : ((a == 2 && b == 0) || (b == 2 && a == 0))
                ? (std::pair<unsigned char, unsigned char>){2, 0}
                : (std::pair<unsigned char, unsigned char>){1, 2});
  }
  std::array<unsigned char, seq_size> seq;
  std::array<unsigned char, seq_size> frac_seq;

 public:
  std::array<unsigned char, seq_size>* getSeqPointer() { return &seq; }
  std::array<unsigned char, seq_size>* getFracSeqPointer() { return &frac_seq; }
  void draw_raw() {
    for (int i = 0; i < seq_size; i++) {
      std::cout << (int)(seq[i]);
    }
    std::cout << ".";
    for (int i = 0; i < seq_size; i++) {
      std::cout << (int)(frac_seq[i]);
    }
    std::cout << "\n";
  }
  void flip_trits() {
    for (int i = 0; i < seq_size; i++) {
      seq[i] = ((seq[i] == 2) ? 1 : (seq[i] == 1) ? 2 : 0);
    }
    for (int i = 0; i < seq_size; i++) {
      frac_seq[i] = ((frac_seq[i] == 2) ? 1 : (frac_seq[i] == 1) ? 2 : 0);
    }
  }

  void operator=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot equate trinary numbers of different size!!");
    } else {
      seq = *inp.getSeqPointer();
      frac_seq = *inp.getFracSeqPointer();
    }
  }
  trinary operator-(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot substract trinary numbers of different size!!");
    }
    trinary<seq_size> new_trinary(0);
    new_trinary += *this;
    new_trinary -= inp;
    return new_trinary;
  }
  void operator-=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot substract trinary numbers of different size!!");
    }
    trinary reverse_inp = inp;
    reverse_inp.flip_trits();
    *this += reverse_inp;
  }
  trinary operator+(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot summarize trinary numbers of different size!!");
    }
    trinary<seq_size> new_trinary(0);
    new_trinary += inp;
    new_trinary += *this;
    return new_trinary;
  }
  double to_double() {
    double res = 0;
    for (int i = 0; i < seq_size; i++) {
      if (seq[i] == 1) {
        res += pow(3, seq_size - 1 - i);
      } else if (seq[i] == 2) {
        res -= pow(3, seq_size - 1 - i);
      }
    }
    for (int i = 0; i < seq_size; i++) {
      if (frac_seq[i] == 1) {
        res += pow(3, -(i + 1));
      } else if (frac_seq[i] == 2) {
        res -= pow(3, -(i + 1));
      }
    }
    return res;
  }
  void operator+=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot summarize trinary numbers of different size!!");
    } else {
      unsigned char left = 0;
      unsigned char left_temp = 0;
      for (int i = seq_size - 1; i > -1; i--) {
        std::pair<unsigned char, unsigned char> rs =
            sum(*(inp.getFracSeqPointer()->begin() + i), frac_seq[i]);
        left_temp = rs.second;
        rs = sum(rs.first, left);
        left = sum(rs.second, left_temp).first;
        frac_seq[i] = rs.first;
      }
      for (int i = seq_size - 1; i > -1; i--) {
        std::pair<unsigned char, unsigned char> rs =
            sum(*(inp.getSeqPointer()->begin() + i), seq[i]);
        left_temp = rs.second;
        rs = sum(rs.first, left);
        left = sum(rs.second, left_temp).first;
        seq[i] = rs.first;
      }
    }
    return;
  }
  template <typename B>
  trinary(B number) {
    std::fill(seq.begin(), seq.begin() + seq_size, 0);
    std::fill(frac_seq.begin(), frac_seq.begin() + seq_size, 0);
    if (pow(2, 8 * sizeof(B)) > pow(3, seq_size)) {
      throw std::logic_error("Sequence size too small for the number!!");
    }
    bool sign = (number < 0);
    unsigned long long whole_part =
        static_cast<unsigned long long>(abs(number / 1));
    unsigned long long pow_10 = pow(10, seq_size);
    unsigned long long frac_part;
    if (sign) {
      frac_part = static_cast<unsigned long long>((abs(number / 1) - number) *
                                                  pow_10 / 10);
    } else {
      frac_part = static_cast<unsigned long long>((number - abs(number / 1)) *
                                                  pow_10 / 10);
    }
    int j = 0;
    while (whole_part > 0) {
      short temp = whole_part % 3;
      whole_part = whole_part / 3;
      if (temp == 2) {
        whole_part++;
      }
      if (!sign) {
        seq[seq_size - j - 1] = (temp == 0 ? 0 : (temp == 1) ? 1 : 2);
      } else {
        seq[seq_size - j - 1] = (temp == 0 ? 0 : (temp == 1) ? 2 : 1);
      }
      j++;
    }
    int accuracy_iterator = 0;
    short left = 0;
    while (accuracy_iterator < seq_size) {
      frac_part *= 3;
      short temp = frac_part / (pow_10 / 10) + left;
      if (temp >= 2) {
        left = 1;
      } else {
        left = 0;
      }
      if (frac_part > pow_10 / 10) {
        frac_part %= (pow_10 / 10);
      }
      if (accuracy_iterator > 0) {
        if (!sign) {
          frac_seq[accuracy_iterator - 1] = (temp == 0     ? 0
                                             : (temp == 1) ? 1
                                             : (temp == 2) ? 2
                                                           : 0);
        } else {
          frac_seq[accuracy_iterator - 1] = (temp == 0     ? 0
                                             : (temp == 1) ? 2
                                             : (temp == 2) ? 1
                                                           : 0);
        }
      }
      accuracy_iterator++;
    }
  }
};

#endif