#pragma once

#include "Optional/UvgRtp.h"
#include "Pipeline/Internal/PipelineSink.h"

#include "CoreMinimal.h"

#include <string>

// Transmits data in an RTP stream
class CITHRUS_API RtpTransmitter : public PipelineSink<1>
{
public:
	RtpTransmitter(const std::string& ip, const int& dstPort, const int& frameRate = 0);
	virtual ~RtpTransmitter();

	virtual void Process() override;

protected:
#ifdef CITHRUS_UVGRTP_AVAILABLE
	uvgrtp::context streamContext_;
	uvgrtp::session* streamSession_;
	uvgrtp::media_stream* stream_;
#endif // CITHRUS_UVGRTP_AVAILABLE
};
