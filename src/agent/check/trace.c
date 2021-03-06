/*
 * Copyright 2014 Nippon Telegraph and Telephone Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "lagopus_apis.h"
#include "openflow13.h"
#include "openflow13packet.h"
#include "lagopus/ofp_pdump.h"

int
main(int argc, const char *const argv[]) {
  struct ofp_header ofp_header = {0x01, 0x02,
           0x03, 0x04
  };
  struct ofp_hello ofp_hello;
  struct ofp_action_output ofp_action_output;
  int i = 123;
  (void) argc;
  (void) argv;

  lagopus_log_set_trace_flags(TRACE_OFPT_HELLO |
                              TRACE_OFPT_FLOW_MOD);

  /* dump ofp_hello. */
  ofp_hello.header = ofp_header;
  lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                    ofp_hello, "<hello> ");


  /* check trace flag. */
  if (lagopus_log_check_trace_flags(TRACE_OFPT_HELLO)) {
    lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HEADER,
                      ofp_hello.header, "<check trace hello header> ");
    lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                      ofp_hello, "<check trace hello> ");
  }

  /* dump ofp_action_output. */
  ofp_action_output.type = 1;
  ofp_action_output.len = 20;
  ofp_action_output.port = 300;
  ofp_action_output.max_len = 4000;
  memset(ofp_action_output.pad, 0 ,sizeof(ofp_action_output.pad));
  lagopus_msg_pdump(TRACE_OFPT_FLOW_MOD, PDUMP_OFP_ACTION_OUTPUT,
                    ofp_action_output, "<action_output> ");

  /* unset TRACE_OFPT_FLOW_MOD. Not dump ofp_action_output. */
  lagopus_log_unset_trace_flags(TRACE_OFPT_FLOW_MOD);
  lagopus_msg_pdump(TRACE_OFPT_FLOW_MOD, PDUMP_OFP_ACTION_OUTPUT,
                    ofp_action_output, "<ERROR : unset flow_mod> ");

  /* set trace_packet_flag. */
  lagopus_log_set_trace_packet_flag(true);
  lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                    ofp_hello, "<set trace_packet_flag hello> ");
  lagopus_msg_pdump(TRACE_OFPT_FLOW_MOD, PDUMP_OFP_ACTION_OUTPUT,
                    ofp_action_output,
                    "<set trace_packet_flag action_output> ");
  /* check trace flag (set trace_packet_flag). */
  if (lagopus_log_check_trace_flags(TRACE_OFPT_HELLO)) {
    lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                      ofp_hello,
                      "<check trace hello(set trace_packet_flag)> ");
  }

  /* unset trace_packet_flag. */
  lagopus_log_set_trace_packet_flag(false);
  lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                    ofp_hello, "<unset trace_packet_flag hello> ");
  lagopus_msg_pdump(TRACE_OFPT_FLOW_MOD, PDUMP_OFP_ACTION_OUTPUT,
                    ofp_action_output,
                    "<ERROR unset trace_packet_flag action_output> ");

  /* other format. */
  lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                    ofp_hello, "<other format> i = %d : ", i);

  /* unset trace_flags. */
  lagopus_log_unset_trace_flags(TRACE_FULL);
  lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                    ofp_hello, "<ERROR : unset flag> ");

  /* check trace flag. */
  if (lagopus_log_check_trace_flags(TRACE_OFPT_HELLO)) {
    lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HEADER,
                      ofp_hello.header, "<ERROR : unset flag> ");
    lagopus_msg_pdump(TRACE_OFPT_HELLO, PDUMP_OFP_HELLO,
                      ofp_hello, "<ERROR : unset flag> ");
  }

  return 0;
}
