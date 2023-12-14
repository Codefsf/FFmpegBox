#pragma once

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavutil/imgutils.h"
    #include "libswscale/swscale.h"
    #include "libavfilter/avfilter.h"
}

#include <string>
#include <vector>

class FFmpegFilter
{
public:
    FFmpegFilter();
    ~FFmpegFilter();

    static std::vector<std::string> GetAllFilter();

    void Init(const std::string& filter_desc);
    void Uninit();

    void SetInput(AVFrame *frame);
    AVFrame *GetOutput();

private:
    AVFilterGraph *filterGraph;
    AVFilterContext *buffersinkCtx;
    AVFilterContext *buffersrcCtx;
    AVFilterInOut *outputs;
    AVFilterInOut *inputs;
    AVFrame *frame;
    AVFrame *filtFrame;
    int64_t pts;
};