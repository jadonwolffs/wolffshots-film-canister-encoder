#include <string>
#include <vector>

class Encoder{
private:
  int asa;
  bool asa_valid;
  char frames;
  bool frames_valid;
  std::string tolerance;
  bool tolerance_valid;
public:
  Encoder();
  Encoder(std::string asa, std::string frames, std::string tolerance);
  ~Encoder();
  // int set_asa(std::string input);
  // int set_frames(std::string input);
  // int set_tolerance(std::string input);
  std::vector<bool> get_asa(void);
  std::vector<bool> get_frames(void);
  std::vector<bool> get_tolerance(void);
  std::vector<std::vector<bool> > get_output(void);
  std::string print_roll(std::vector<std::vector<bool> > output);
  int check_valid(void);

};
