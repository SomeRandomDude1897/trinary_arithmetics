#ifndef TRINARY
#define TRINARY

#include <cmath>
#include <vector>

template <size_t seq_size>

class trinary {
 private:
  std::vector<unsigned char> seq;
  std::vector<unsigned char> frac_seq;

 public:
  template <typename B>
  std::vector<unsigned char>* getSeqPointer() {
    return *seq;
  }
  std::vector<unsigned char>* getFracSeqPointer() { return *frac_seq; }
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

  void operator=(trinary inp) {
    if (inp.seq.size() != seq.size()) {
      throw std::logic_error("Cannot equate numbers of different size!!");
    } else {
      seq = &inp.getSeqPointer();
      frac_seq = &inp.getFracSeqPointer();
    }
  }
  void operator+=(trinary inp) {
    if (inp.seq.size() != seq.size()) {
      throw std::logic_error("Cannot summarize numbers of different size!!");
    }
    unsigned char left = 0;
    trinary new_<seq>(0);
    for (int i = seq_size; i > -1; i--) {
      unsigned char rs = &inp.getFracSeqPointer()[i] + frac_seq[i] + left;
      left = 0;
      if (rs > 2) {
        left = 1;
        frac_seq[i] = 2;
      } else {
        frac_seq[i] = rs;
      }
    }
    for (int i = 0; i < seq_size; i++) {
      unsigned char rs = &inp.getSeqPointer()[i] + seq[i] + left;
      left = 0;
      if (rs > 2) {
        left = 1;
        seq[i] = 2;
      } else {
        seq[i] = rs;
      }
    }
  }
  trinary(B number = 0.0) {
    seq.reserve(seq_size);
    frac_seq.reserve(seq_size);
    std::cout << sizeof(B) << '\n';
    if (pow(2, 8 * sizeof(B)) > pow(3, seq_size)) {
      throw std::logic_error("Sequence size too small for the number!!");
    }
    bool sign = (number < 0);
    unsigned long long whole_part =
        abs(static_cast<unsigned long long>(number / 1));
    unsigned long long pow_10 = pow(10, seq_size);
    unsigned long long frac_part =
        static_cast<unsigned long long>((number - whole_part) * pow_10 / 10);
    std::vector<short> temp_seq(seq_size);
    int j = 0;
    while (whole_part > 0) {
      short temp = whole_part % 3;
      whole_part = whole_part / 3;
      if (temp == 2) {
        whole_part++;
      }
      temp_seq[seq_size - j - 1] = (temp == 0 ? 0 : (temp == 1) ? 1 : 2);
      j++;
    }
    for (int x = seq_size - 1; x > -1; x--) {
      if (sign) {
        if ((temp_seq[x]) == 2) {
          seq[x] = static_cast<unsigned char>(1);
        } else if (temp_seq[x] == 1) {
          seq[x] = static_cast<unsigned char>(2);
        } else {
          seq[x] = static_cast<unsigned char>(0);
        }
      } else {
        seq[x] = static_cast<unsigned char>(temp_seq[x]);
      }
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
      frac_seq.push_back(static_cast<unsigned char>(temp == 0     ? 0
                                                    : (temp == 1) ? 1
                                                    : (temp == 2) ? 2
                                                                  : 0));
      accuracy_iterator++;
    }
  }
};

#endif