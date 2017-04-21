extern "C" {
#include "classification.h"
}

#include <vector>
#include "cppcaffe/classification.hpp"

Classifier NewClassifier(const char *model_file,
                                 const char *trained_file, const char *mean_file, const char *label_file) {
  return (Classifier)(
      new cppcaffe::Classifier(model_file, trained_file, mean_file, label_file));
}

double *Predict(Classifier predictor, const char *imgname) {
//  std::vector<double> ret =
//      ((cppcaffe::Classifier *)predictor)->predict(imgname);
//  if(ret.empty()) {
//  	return NULL;
//  }
//  double *fret = (double *)malloc(sizeof(double) * ret.size());
//  for (int i = 0; i < ret.size(); i++) {
//    fret[i] = ret[i];
//  }
//  return fret;


      cv::Mat img = cv::imread(imgname, -1);
      CHECK(!img.empty()) << "Unable to decode image " << file;
      std::vector<Prediction> predictions = classifier.Classify(img);

        /* Print the top N predictions. */
        for (size_t i = 0; i < predictions.size(); ++i) {
          Prediction p = predictions[i];
          std::cout << std::fixed << std::setprecision(4) << p.second << " - \""
                    << p.first << "\"" << std::endl;
        }

}

//int NClass(Classifier predictor) {
//  return ((cppcaffe::Classifier *)predictor)->nclass();
//}

//int main(int argc, char** argv) {
//
//}