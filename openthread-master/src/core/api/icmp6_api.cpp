/*
 *  Copyright (c) 2016, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread ICMPv6 API.
 */

#include "openthread-core-config.h"

#include <openthread/icmp6.h>

#include "openthread-instance.h"

#include <iostream>
#include <fstream>

using namespace ot;

static int icmpcounter = 0;

void write_payload_to_file(uint8_t *ptr, size_t len) 
{
    std::ofstream fp;
    char filename[128];
    sprintf(filename,"/home/bart/Desktop/icmp/echo%d.bin",icmpcounter);
    fp.open(filename, std::ios::out | std::ios::binary);
    fp.write((char*)ptr, len);
    icmpcounter++;
}

bool otIcmp6IsEchoEnabled(otInstance *aInstance)
{
    return aInstance->mIp6.GetIcmp().IsEchoEnabled();
}

void otIcmp6SetEchoEnabled(otInstance *aInstance, bool aEnabled)
{
    aInstance->mIp6.GetIcmp().SetEchoEnabled(aEnabled);
}

otError otIcmp6RegisterHandler(otInstance *aInstance, otIcmp6Handler *aHandler)
{
    return aInstance->mIp6.GetIcmp().RegisterHandler(*static_cast<Ip6::IcmpHandler *>(aHandler));
}

otError otIcmp6SendEchoRequest(otInstance *aInstance, otMessage *aMessage,
                               const otMessageInfo *aMessageInfo, uint16_t aIdentifier)
{
	//Message *bMessage = static_cast<Message *>(aMessage);
	//write_payload_to_file(bMessage->GetData(), otMessageGetLength(aMessage));
    return aInstance->mIp6.GetIcmp().SendEchoRequest(*static_cast<Message *>(aMessage),
                                                     *static_cast<const Ip6::MessageInfo *>(aMessageInfo),
                                                     aIdentifier);
}
