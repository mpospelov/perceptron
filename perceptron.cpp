#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#define MAX_CYCLES_COUNT 50

using namespace std;

class Perceptron {

  double w0, w1, w2,
         **input_vec, *output_vec,
         delta0, delta1, delta2;

  enum errors { FILE_ERROR };
  int input_file_lines_count;

  static const char gnuplot_file_name[], zero_file_name[], one_file_name[];

  ifstream input_file;
  ofstream gnuplot_file, zero_file, one_file;

  public:
    Perceptron(char *input_file_name){
      srand(time(NULL));

      w0 = double(rand())/RAND_MAX;
      w1 = double(rand())/RAND_MAX;
      w2 = double(rand())/RAND_MAX;
      init_file(&zero_file, Perceptron::zero_file_name);
      init_file(&one_file, Perceptron::one_file_name);
      init_file(&input_file, input_file_name);
      init_file(&gnuplot_file, Perceptron::gnuplot_file_name);

      input_file_lines_count = std::count(
        istreambuf_iterator<char>(input_file),
        istreambuf_iterator<char>(), '\n');

      input_vec = new double*[input_file_lines_count];
      for (int i = 0; i < input_file_lines_count; i++){
        input_vec[i] = new double[3];
      }

      output_vec = new double[input_file_lines_count];

      init_gnuplot();
      read_input_file();

    };

    bool output(double x1, double x2) {
      return w0 + x1 * w1 + x2 * w2 >= 0;
    }

    bool teach(){

      cout_iteration(-1, w0, w1, w2);
      for(int t = 0; t < MAX_CYCLES_COUNT; t++){
        for(int i = 0; i < input_file_lines_count; i++){
          double output_val = output_vec[i],
                 *c_vec = input_vec[i];

          bool output_result = output(input_vec[i][1], input_vec[i][2]);

          put_line_to_gnuplot_file(w0, w1, w2);

          delta0 = c_vec[0] * (output_val - output_result);
          delta1 = c_vec[1] * delta0;
          delta2 = c_vec[2] * delta0;

          w0 += delta0;
          w1 += delta1;
          w2 += delta2;

          put_line_to_gnuplot_file(w0, w1, w2);
          cout_iteration(i, w0, w1, w2);

        }
      }

      gnuplot_file << "pause -1\n";
      input_file.close();
      gnuplot_file.close();
      zero_file.close();
      one_file.close();

      return true;
    };

  private:

    void cout_iteration(int i, double w0, double w1, double w2){
      cout << "i = " << i << "\t"
           << "w0 = " << w0 << "\t"
           << "w1 = " << w1<< "\t"
           << "w2 = " << w2 << endl;
    }

    void put_line_to_gnuplot_file(double w0, double w1, double w2){
      gnuplot_file << "plot '" << zero_file_name << "' using 1:2 title '\"0\" points set' with points linecolor rgb 'blue',\\\n";
      gnuplot_file << "'" << one_file_name << "' using 1:2 title '\"1\" points set' with points linecolor rgb 'red',\\\n";
      gnuplot_file << '(' << -w1 / w2 << ")*x+(" << -w0 / w2 << ") linecolor rgb 'black'\n";
      gnuplot_file << "pause 0.01\n";
    }

    void init_file(ifstream *file, const char *file_name){
      file -> open(file_name);
      if (!file -> is_open()) {
        cout << "\nError: can't open file: \"" << file_name << "\"\n";
        throw FILE_ERROR;
      }
    }

    void init_file(ofstream *file, const char *file_name){
      file -> open(file_name);
      if (!file -> is_open()) {
        cout << "\nError: can't open file: \"" << file_name << "\"\n";
        throw FILE_ERROR;
      }
    }

    void init_gnuplot(){
      gnuplot_file << "reset\n";
      gnuplot_file << "set terminal x11\n";
      gnuplot_file << "set size 1,1\n";
      gnuplot_file << "set xrange [-3:8]\n";
      gnuplot_file << "set yrange [-3:8]\n";
      gnuplot_file << "set xtics 1\n";
      gnuplot_file << "set ytics 1\n";
      gnuplot_file << "set grid xtics ytics\n";
      gnuplot_file << "plot 'zero.dat' using 1:2 title '\"0\" points set' with points linecolor rgb 'blue',\\\n";
      gnuplot_file << "'one.dat' using 1:2 title '\"1\" points set' with points linecolor rgb 'red',\\\n";
      gnuplot_file << '(' << -w1 / w2 << ")*x+(" << -w0 / w2 << ") linecolor rgb 'black'\n";
      gnuplot_file << "pause 1.5\n";
    }

    void read_input_file(){
      input_file.seekg(0);
      for (int i = 0; i < input_file_lines_count; i++) {
        input_vec[i][0] = 1;
        input_file >> input_vec[i][1] >> input_vec[i][2] >> output_vec[i];

        if (output_vec[i] == 0){
          zero_file << input_vec[i][1] << ' ' << input_vec[i][2] << endl;
        }else{
          one_file << input_vec[i][1] << ' ' << input_vec[i][2] << endl;
        }
      }
    }

};

const char Perceptron::gnuplot_file_name[] = "gnuplot_out.plt",
           Perceptron::zero_file_name[] = "zero.dat",
           Perceptron::one_file_name[] = "one.dat";

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "\nBad input arguments!";
    cout << " Usage:\n$neuron <input_file_name>\n";
    return 1;
  }

  Perceptron *neuron = new Perceptron(argv[1]);

  if (!neuron -> teach()){
    return 1;
  }

  return 0;
}
