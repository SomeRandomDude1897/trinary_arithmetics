#ifndef TRINARY
#define TRINARY

#include <array>
#include <cmath>

template <size_t seq_size>

class trinary {
  typedef unsigned char trit;
  typedef std::array<trit, 3> tryte;

 private:
  std::pair<trit, trit> sum(trit a, trit b) {
    return ((a + b == 0)             ? (std::pair<trit, trit>){0, 0}
            : (a + b == 1)           ? (std::pair<trit, trit>){1, 0}
            : (a + b == 3)           ? (std::pair<trit, trit>){0, 0}
            : (a == 1 && a + b == 2) ? (std::pair<trit, trit>){2, 1}
            : ((a == 2 && b == 0) || (b == 2 && a == 0))
                ? (std::pair<trit, trit>){2, 0}
                : (std::pair<trit, trit>){1, 2});
  }
  trit multiply(trit a, trit b) {
    return ((a == 0 || b == 0)   ? 0
            : (a == 1 && b == 1) ? 1
            : (a == 2 ^ b == 2)  ? 2
                                 : 1);
  }
  std::array<trit, seq_size> seq;

  std::array<trit, seq_size> frac_seq;

 public:
  std::array<trit, seq_size>* getSeqPointer() { return &seq; }
  std::array<trit, seq_size>* getFracSeqPointer() { return &frac_seq; }
  friend std::ostream& operator<<(std::ostream& os, trinary inp) {
    for (int i = 0; i < inp.getSeqPointer()->size(); i++) {
      os << static_cast<int>(*(inp.getSeqPointer()->begin() + i));
    }
    os << ".";
    for (int i = 0; i < seq_size; i++) {
      os << static_cast<int>(*(inp.getFracSeqPointer()->begin() + i));
    }
    return os;
  }
  void flip_trits() {
    for (int i = 0; i < seq_size; i++) {
      seq[i] = ((seq[i] == 2) ? 1 : (seq[i] == 1) ? 2 : 0);
    }
    for (int i = 0; i < seq_size; i++) {
      frac_seq[i] = ((frac_seq[i] == 2) ? 1 : (frac_seq[i] == 1) ? 2 : 0);
    }
  }
  trinary operator*(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot summarize trinary numbers of different size!!");
    }
    trinary<seq_size> new_trinary(0);
    new_trinary += inp;
    new_trinary *= *this;
    return new_trinary;
  }
  trinary operator/(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot summarize trinary numbers of different size!!");
    }
    trinary<seq_size> new_trinary(0);
    new_trinary += *this;
    new_trinary /= inp;
    return new_trinary;
  }
  void operator/=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot divide trinary numbers of different size!!");
    }
    if (inp.to_double() != 0) {
      trinary conjugate(1.0 / inp.to_double());
      *this *= conjugate;
    } else {
      throw std::logic_error("Cannot divide number by zero!!");
    }
  }
  void operator*=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot multiply trinary numbers of different size!!");
    }
    double res = 0;
    std::array<trit, seq_size * 2> full_ternary_1;
    std::array<trit, seq_size * 2> full_ternary_2;
    for (int i = 0; i < seq_size; i++) {
      full_ternary_1[i] = seq[i];
      full_ternary_2[i] = *(inp.getSeqPointer()->begin() + i);
    }
    for (int i = 0; i < seq_size; i++) {
      full_ternary_1[i + seq_size] = frac_seq[i];
      full_ternary_2[i + seq_size] = *(inp.getFracSeqPointer()->begin() + i);
    }

    for (int i = 0; i < seq_size * 2; i++) {
      double delta = 0;
      for (int j = 0; j < seq_size * 2; j++) {
        auto delta_multiply = multiply(full_ternary_1[j], full_ternary_2[i]);
        if (delta_multiply == 2) {
          delta -=
              pow(3, static_cast<int>(seq_size - j + (seq_size - i - 1) - 1));
        } else if (delta_multiply == 1) {
          delta +=
              pow(3, static_cast<int>(seq_size - j + (seq_size - i - 1) - 1));
        }
      }
      res += delta;
    }
    trinary<seq_size> global_delta(res);
    *this = global_delta;
  }

  void operator=(trinary inp) {
    if (inp.getSeqPointer()->size() != seq_size) {
      throw std::logic_error(
          "Cannot equate trinary numbers of different size!!");
    }
    seq = *inp.getSeqPointer();
    frac_seq = *inp.getFracSeqPointer();
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
      trit left = 0;
      trit left_temp = 0;
      for (int i = seq_size - 1; i > -1; i--) {
        std::pair<trit, trit> rs =
            sum(*(inp.getFracSeqPointer()->begin() + i), frac_seq[i]);
        left_temp = rs.second;
        rs = sum(rs.first, left);
        left = sum(rs.second, left_temp).first;
        frac_seq[i] = rs.first;
      }
      for (int i = seq_size - 1; i > -1; i--) {
        std::pair<trit, trit> rs =
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
    bool sign = (number < 0);
    unsigned long long whole_part =
        static_cast<unsigned long long>(abs(number / 1));
    double frac_part;
    if (sign) {
      frac_part = ((abs(number / 1) + number));
    } else {
      frac_part = ((number - abs(number / 1)));
    }
    if (fabs(frac_part) > 0.5) {
      whole_part++;
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
    if (frac_part != 0) {
      if (fabs(frac_part) > 0.5) {
        sign = !sign;
        frac_part = 1 - fabs(frac_part);
      }
      int tristate = 1;
      while (pow(3, -(tristate + 1)) > frac_part) {
        tristate++;
      }

      if (sign) {
        frac_seq[tristate - 1] = 2;
      } else {
        frac_seq[tristate - 1] = 1;
      }
      int accuracy_iterator = tristate;
      int power = -tristate;

      double balance = frac_part;
      bool recount_flag = true;
      while (accuracy_iterator < seq_size) {
        double comp_value = pow(3, power);
        if (recount_flag) {
          if (balance < 0) {
            balance = comp_value + balance;
          } else if (power == -1) {
            balance = comp_value - balance;
          } else {
            balance = balance - comp_value;
          }
        }
        if (fabs(balance) >= comp_value / 6) {
          if (balance < 0) {
            frac_seq[accuracy_iterator] = ((sign) ? 2 : 1);
          } else {
            frac_seq[accuracy_iterator] = ((sign) ? 1 : 2);
          }
          recount_flag = true;
        } else {
          frac_seq[accuracy_iterator] = 0;
          recount_flag = false;
        }
        power--;
        accuracy_iterator++;
      }
    }
  }
};

#endif