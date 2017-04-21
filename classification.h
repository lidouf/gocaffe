#ifndef CAFFE_H
#define CAFFE_H

typedef void* Classifier;

Classifier NewClassifier(const char * model_file, const char * trained_file);
double * Predict(Classifier predictor, const char * imgname);
int NClass(Classifier predictor);

#endif