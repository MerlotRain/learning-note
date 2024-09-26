#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}



bool covert_h265_to_h264(const char *input_filename,  const char *output_filename)
{
    av_register_all();
    avcodec_register_all();
    av_log_set_callback(ffmpegLogCallBack);
    int ret = 0;
    AVFormatContext *inputFormatCtx = NULL;
    AVFormatContext *outputFormatCtx = NULL;
    AVCodecContext *decoderCtx = NULL;
    AVCodecContext *encoderCtx = NULL;
    AVStream *outStream = NULL;
    // Open input file
    if (avformat_open_input(&inputFormatCtx, input_filename, NULL, NULL) < 0)
    {
        fprintf(stderr, "Could not open input file.\n");
        return false;
    }
    avformat_find_stream_info(inputFormatCtx, NULL);
    // Create output context
    avformat_alloc_output_context2(&outputFormatCtx, NULL, "mp4", output_filename);
    if (!outputFormatCtx)
    {
        fprintf(stderr, "Could not create output context.\n");
        return false;
    }
    // 如果不是hevc，则不转换，是否绝对安全呢？
    if (inputFormatCtx->streams[0]->codecpar->codec_id != AV_CODEC_ID_HEVC)
    {
        return false;
    }
    // Find and open the H.265 decoder
    AVCodec *decoder = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    decoderCtx = avcodec_alloc_context3(decoder);
    avcodec_parameters_to_context(decoderCtx, inputFormatCtx->streams[0]->codecpar);
    ret = avcodec_open2(decoderCtx, decoder, NULL);
    // Find and open the H.264 encoder
    AVCodec *encoder = avcodec_find_encoder(AV_CODEC_ID_H264);
    encoderCtx = avcodec_alloc_context3(encoder);
    encoderCtx->codec = encoder;
    encoderCtx->bit_rate = decoderCtx->bit_rate;
    encoderCtx->width = decoderCtx->width;
    encoderCtx->height = decoderCtx->height;
    encoderCtx->time_base.den = decoderCtx->time_base.den;
    encoderCtx->time_base.num = decoderCtx->time_base.num;
    encoderCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    encoderCtx->bit_rate = 4000000;// Set bitrate
    encoderCtx->profile = FF_PROFILE_H264_MAIN;
    outStream = avformat_new_stream(outputFormatCtx, encoder);
    avcodec_parameters_from_context(outStream->codecpar, encoderCtx);
    ret = avcodec_open2(encoderCtx, encoder, NULL);
    // Open output file
    avio_open(&outputFormatCtx->pb, output_filename, AVIO_FLAG_WRITE);
    avformat_write_header(outputFormatCtx, NULL);
    // Main processing loop
    AVPacket *input_packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    int response;
    while (av_read_frame(inputFormatCtx, input_packet) >= 0)
    {
        if (input_packet->stream_index == 0)
        {
            response = avcodec_send_packet(decoderCtx, input_packet);
            while (response >= 0)
            {
                response = avcodec_receive_frame(decoderCtx, frame);
                if (response >= 0)
                {
                    // Encode the frame
                    response = avcodec_send_frame(encoderCtx, frame);
                    while (response >= 0)
                    {
                        AVPacket *output_packet = av_packet_alloc();
                        response = avcodec_receive_packet(encoderCtx, output_packet);
                        if (response >= 0)
                        {
                            output_packet->stream_index = outStream->index;
                            av_interleaved_write_frame(outputFormatCtx, output_packet);
                            av_packet_free(&output_packet);
                        }
                    }
                }
            }
        }
        av_packet_unref(input_packet);
    }
    // Flush the encoder
    avcodec_send_frame(encoderCtx, NULL);
    while (avcodec_receive_packet(encoderCtx, input_packet) >= 0)
    {
        input_packet->stream_index = outStream->index;
        av_interleaved_write_frame(outputFormatCtx, input_packet);
        av_packet_unref(input_packet);
    }
    // Cleanup
    av_write_trailer(outputFormatCtx);
    avcodec_free_context(&decoderCtx);
    avcodec_free_context(&encoderCtx);
    av_frame_free(&frame);
    av_packet_free(&input_packet);
    avformat_close_input(&inputFormatCtx);
    avformat_free_context(outputFormatCtx);
    return true;
}
