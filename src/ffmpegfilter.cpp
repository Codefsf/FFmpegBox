#include "ffmpegfilter.h"

#include <iostream>

FFmpegFilter::FFmpegFilter()
{
    filterGraph = nullptr;
    buffersinkCtx = nullptr;
    buffersrcCtx = nullptr;
    outputs = nullptr;
    inputs = nullptr;
    frame = nullptr;
    filtFrame = nullptr;
    pts = 0;
}

FFmpegFilter::~FFmpegFilter()
{
    unInit();
}

std::vector<std::string> FFmpegFilter::getAllFilter()
{
    std::vector<std::string> filters;
    const AVFilter* filter = nullptr;
    void* opaque = nullptr;

    while ((filter = av_filter_iterate(&opaque)))
    {
        filters.push_back(filter->name);
    }

    return filters;
}

void FFmpegFilter::init(const std::string& filter_desc)
{
    if (filter_desc.empty())
    {
        return;
    }

    int ret = 0;
}

void FFmpegFilter::unInit()
{
    if (filterGraph != nullptr)
    {
        avfilter_graph_free(&filterGraph);
        filterGraph = nullptr;
    }

    if (buffersinkCtx != nullptr)
    {
        avfilter_free(buffersinkCtx);
        buffersinkCtx = nullptr;
    }

    if (buffersrcCtx != nullptr)
    {
        avfilter_free(buffersrcCtx);
        buffersrcCtx = nullptr;
    }

    if (outputs != nullptr)
    {
        avfilter_inout_free(&outputs);
        outputs = nullptr;
    }

    if (inputs != nullptr)
    {
        avfilter_inout_free(&inputs);
        inputs = nullptr;
    }

    if (frame != nullptr)
    {
        av_frame_free(&frame);
        frame = nullptr;
    }

    if (filtFrame != nullptr)
    {
        av_frame_free(&filtFrame);
        filtFrame = nullptr;
    }
}

void FFmpegFilter::setInput(AVFrame *frame)
{
    this->frame = frame;
}

AVFrame* FFmpegFilter::getOutput()
{
    return filtFrame;
}


