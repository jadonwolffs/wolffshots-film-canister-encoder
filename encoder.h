#include <string>
#include <vector>

class Encoder{
private:
  int asa;
  const std::vector<int> asa_l={25,32,40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400,500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 4000, 5000};
  const std::vector<std::vector<bool> > asa_enc_l = {{0,0,0,1,0},{0,0,0,0,1},{0,0,0,1,1},{1,0,0,1,0},{1,0,0,0,1},{1,0,0,1,1},{0,1,0,1,0},{0,1,0,0,1},{0,1,0,1,1},{1,1,0,1,0},{1,1,0,0,1},{1,1,0,1,1},{0,0,1,1,0},{0,0,1,0,1},{0,0,1,1,1},{1,0,1,1,0},{1,0,1,0,1},{1,0,1,1,1},{0,1,1,1,0},{0,1,1,0,1},{0,1,1,1,1},{1,1,1,1,0},{1,1,1,0,1},{1,1,1,1,1},{0,0,0,0,0}};
  bool asa_valid;
  char frames;
  bool frames_valid;
  std::string tolerance;
  bool tolerance_valid;
public:
  Encoder();
  Encoder(std::string asa, std::string frames, std::string tolerance);
  Encoder(int asa, char frames, std::string tolerance);
  ~Encoder();
  std::vector<bool> get_asa(void);
  std::vector<bool> get_frames(void);
  std::vector<bool> get_tolerance(void);
  std::vector<std::vector<bool> > get_output(void);
  std::string print_roll(std::vector<std::vector<bool> > output);
  int check_valid(void);
  std::vector<std::vector<bool> > get_mod_output(std::string mod_s);

};
