#ifndef CAFFE_MULTI_FRAME_DATA_LAYER_HPP_
#define CAFFE_MULTI_FRAME_DATA_LAYER_HPP_

#include <string>
#include <utility>
#include <vector>

#include "boost/scoped_ptr.hpp"
#include "hdf5.h"

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/data_transformer.hpp"
#include "caffe/filler.hpp"
#include "caffe/internal_thread.hpp"
#include "caffe/layer.hpp"
#include "caffe/layers/base_data_layer.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/db.hpp"
#include "caffe/util/rng.hpp"

namespace caffe {

    /**
 * @brief Provides data to the Net from video files.
 *
 * TODO(dox): thorough documentation for Forward and proto params.
 */
template <typename Dtype>
class MultiFrameDataLayer : public BasePrefetchingDataLayer<Dtype> {
public:
    explicit MultiFrameDataLayer(const LayerParameter& param)
    : BasePrefetchingDataLayer<Dtype>(param) {}
    virtual ~MultiFrameDataLayer();
    virtual void DataLayerSetUp(const vector<Blob<Dtype>*>& bottom,
            const vector<Blob<Dtype>*>& top);

    virtual inline const char* type() const { return "MultiFrameData"; }
    virtual inline int ExactNumBottomBlobs() const { return 0; }
    virtual inline int ExactNumTopBlobs() const { return 2; }

protected:
    shared_ptr<Caffe::RNG> prefetch_rng_;
    shared_ptr<Caffe::RNG> prefetch_rng_2_;
    shared_ptr<Caffe::RNG> prefetch_rng_1_;
    shared_ptr<Caffe::RNG> frame_prefetch_rng_;
    virtual void ShuffleVideoClips();
    virtual void load_batch(Batch<Dtype>* batch);

    // vector< std::pair< vector<std::string>, int> > lines_;
    vector<std::pair<std::string, int> > lines_;
    vector<int> lines_duration_;
    int lines_id_;
};

}  // namespace caffe

#endif  // CAFFE_MULTI_FRAME_DATA_LAYER_HPP_

