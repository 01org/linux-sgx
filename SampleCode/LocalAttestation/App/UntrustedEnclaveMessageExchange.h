/*
 * Copyright (C) 2011-2020 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include "sgx_eid.h"
#include "error_codes.h"
#include "datatypes.h"
#include "sgx_urts.h"
#include "dh_session_protocol.h"
#include "sgx_dh.h"
#include <cstddef>


#ifndef ULOCALATTESTATION_H_
#define ULOCALATTESTATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Function Description: This is OCALL interface for initiator enclave to get ECDH message 1 and session id from responder enclave 
 * Parameter Description:
 *      [input, output] dh_msg1: pointer to ecdh msg1 buffer, this buffer is alloated in initiator enclave and filled by reponser enclave
 *      [output] session_id: pointer to session id which is allocated by responder enclave
 * */
uint32_t session_request_ocall(sgx_dh_msg1_t* dh_msg1, uint32_t* session_id);

/* Function Description: This is OCALL interface for initiator enclave to send ECDH message 2 to responder enclave, and receive ECDH message 3 from responder enclave
 * Parameter Description:
 *      [input] dh_msg2: this is pointer to ECDH message 2 generated by initiator enclave
 *      [input, output]dh_msg3: this is pointer to ECDH message 3, this buffer is allocated in initiator enclave and filled by respoonder enclave
 *      [input] session_id: this is session id allocated by responder enclave
 * */
uint32_t exchange_report_ocall(sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id);

/* Function Description: This is OCALL interface for initiator enclave to send request message(encrypted) to responder enclave, and receive response message from responder enclave
 * Parameter Description:
 *      [input] session_id: this is session id allocated by responder enclave
 *      [input] req_message: this is pointer to request message
 *      [input] req_message_size: this is request message size
 *      [input] max_payload_size: this is maxium payload size in response message
 *      [input, output] this is pointer to response message, the buffer is allocated by initiator enclave and filled by responder enclave
 *      [input] response message size
 * */
uint32_t send_request_ocall(uint32_t session_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size);


/* Function Description: this is OCALL interface for initiator enclave to close secure session 
 * Parameter Description:
 *      [input] session_id: this is session id allocated by responder enclave
 * */
uint32_t end_session_ocall(uint32_t session_id);

#ifdef __cplusplus
}
#endif

#endif
