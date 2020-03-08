//#include <caffe/caffe.hpp>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <memory>
#include "caffe/net.hpp"
#include "caffe/common.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"
 
using namespace caffe;
using namespace std;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

void print_model() {
  NetParameter proto;
  string trained_file = "./models/resnet50/ResNet-50-model.caffemodel";
  ReadProtoFromBinaryFile(trained_file, &proto);
  WriteProtoToTextFile(proto, "test.prototxt");
}

void read_model() {
  string model_file = "./models/resnet50/ResNet-50-deploy.prototxt";
  string trained_file = "./models/resnet50/ResNet-50-model.caffemodel";
  std::shared_ptr<Net<float> > net_;
  net_.reset(new Net<float>(model_file, TEST));
  net_->CopyTrainedLayersFrom(trained_file);
  net_->Forward();
}
 
int main()
{
   print_model();
   read_model();
   return 0;
}
