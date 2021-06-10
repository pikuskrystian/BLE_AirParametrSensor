/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* \file
*
* ROM symbols definitions file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */
rom_entry_point = 0x03000738;
ahi_init = 0x030030e5;
APP_RestoreBleReg = 0x030008b5;
APP_SaveBleReg = 0x03000921;
ble_config = 0x040003c4;
co_bdaddr_compare = 0x03006c07;
co_list_extract = 0x03006c87;
co_list_find = 0x03006cf3;
co_list_init = 0x03006d09;
co_list_merge = 0x03006da9;
co_list_pop_front = 0x03006e29;
co_list_push_back = 0x03006e3b;
co_list_size = 0x03006e5d;
co_null_bdaddr = 0x0302c2ac;
dbg_default_handler = 0x0302c3c8;
dbg_init = 0x03006f9d;
dbg_platform_reset_complete = 0x03006fc1;
dbg_state = 0x04000025;
ea_elt_create = 0x030071fd;
ea_elt_insert = 0x03007219;
ea_elt_remove = 0x03007559;
ea_finetimer_isr = 0x030075e1;
ea_init = 0x030076e1;
ea_interval_create = 0x03007709;
ea_interval_duration_req = 0x03007745;
ea_interval_insert = 0x030077f9;
ea_interval_remove = 0x03007805;
ea_offset_req = 0x03007815;
ea_sw_isr = 0x03007aa9;
ea_time_get_halfslot_rounded = 0x03007ad1;
ea_timer_target_get = 0x03007b21;
em_buf_env = 0x0400011c;
em_buf_rx_buff_addr_get = 0x030083d5;
em_buf_rx_free = 0x030083f9;
em_buf_tx_free = 0x03008429;
enable_ble_sleep = 0x030084d5;
error = 0x0400003c;
h4tl_env = 0x040002c8;
hci_acl_tx_data_alloc = 0x0300e869;
hci_acl_tx_data_received = 0x0300e92d;
hci_cmd_desc_tab_ctrl_bb = 0x0302bd04;
hci_cmd_desc_tab_info_par = 0x0302bd7c;
hci_cmd_desc_tab_lk_ctrl = 0x0302bce0;
hci_cmd_desc_tab_stat_par = 0x0302bdb8;
hci_cmd_desc_tab_vs = 0x0302c028;
hci_cmd_reject = 0x0300ef19;
hci_env = 0x04000290;
hci_fc_check_host_available_nb_acl_packets = 0x0300fbb9;
hci_flush_cmd_handler = 0x0300fbfd;
hci_host_buf_size_cmd_handler = 0x0300fc3d;
hci_host_nb_cmp_pkts_cmd_handler = 0x0300fc59;
hci_init = 0x0300fd45;
hci_le_create_con_cancel_cmd_handler = 0x030101d5;
hci_le_enh_privacy_info_cmd_handler = 0x030105e1;
hci_le_generate_dhkey_cmd_handler = 0x03010711;
hci_le_ltk_req_reply_cmd_handler = 0x0301087d;
hci_le_rand_cmd_handler = 0x03010ae5;
hci_le_rd_adv_ch_tx_pw_cmd_handler = 0x03010b35;
hci_le_rd_buff_size_cmd_handler = 0x03010bd5;
hci_le_rd_local_p256_public_key_cmd_handler = 0x03010c61;
hci_le_rd_chnl_map_cmd_handler = 0x03010c09;
hci_le_rd_local_supp_feats_cmd_handler = 0x03010d3d;
hci_le_rd_max_data_len_cmd_handler = 0x03010db1;
hci_le_rd_suggted_dft_data_len_cmd_handler = 0x030110c1;
hci_le_rd_rem_used_feats_cmd_handler = 0x03010f61;
hci_le_rd_supp_states_cmd_handler = 0x030110ed;
hci_le_rd_phy_cmd_handler = 0x03010e41;
hci_le_rd_wl_size_cmd_handler = 0x0301111d;
hci_le_set_adv_data_cmd_handler = 0x0301136d;
hci_le_set_data_len_cmd_handler = 0x03011465;
hci_le_set_dft_phy_cmd_handler = 0x030114fd;
hci_le_set_evt_mask_cmd_handler = 0x03011529;
hci_le_set_rand_add_cmd_handler = 0x03011625;
hci_le_set_scan_param_cmd_handler = 0x030116c5;
hci_le_set_scan_rsp_data_cmd_handler = 0x030116eb;
hci_le_test_mode_mngt_cmd_handler = 0x0301185d;
hci_le_wl_mngt_cmd_handler = 0x0301190d;
hci_le_wr_suggted_dft_data_len_cmd_handler = 0x0301198d;
hci_look_for_dbg_evt_desc = 0x03011a5d;
hci_look_for_evt_desc = 0x03011a85;
hci_look_for_le_evt_desc = 0x03011ab5;
hci_rd_auth_payl_to_cmd_handler = 0x03011be5;
hci_rd_bd_addr_cmd_handler = 0x03011c79;
hci_rd_buff_size_cmd_handler = 0x03011cd1;
hci_rd_local_supp_cmds_cmd_handler = 0x03011d61;
hci_rd_local_supp_feats_cmd_handler = 0x03011d91;
hci_rd_local_ver_info_cmd_handler = 0x03011e29;
hci_rd_rssi_cmd_handler = 0x03011fc1;
hci_rd_tx_pwr_lvl_cmd_handler = 0x03012015;
hci_reset = 0x0301208d;
hci_set_ctrl_to_host_flow_ctrl_cmd_handler = 0x0301229d;
hci_set_evt_mask_cmd_handler = 0x030122cf;
hci_set_evt_mask_page_2_cmd_handler = 0x030122e7;
hci_tl_env = 0x040002ac;
hci_tx_done = 0x03012399;
hci_util_pack = 0x030126b1;
hci_util_unpack = 0x030127d3;
hci_wr_auth_payl_to_cmd_handler = 0x0301298d;
ke_event_callback_set = 0x03013f4d;
ke_event_clear = 0x03013f65;
ke_flush = 0x0301408d;
ke_free = 0x030140cd;
ke_init = 0x030141c9;
ke_malloc = 0x03014245;
ke_msg_alloc = 0x0301440d;
ke_msg_free = 0x030144f9;
ke_msg_send_basic = 0x03014559;
ke_sleep_check = 0x03014643;
ke_state_get = 0x03014655;
ke_state_set = 0x03014689;
ke_task_create = 0x03014755;
ke_timer_active = 0x03014a45;
ke_timer_clear = 0x03014a8d;
ke_timer_set = 0x03014bb9;
ke_timer_target_get = 0x03014c95;
llc_auth_payl_real_to_ind_handler = 0x03016ec5;
llc_ch_assess_get_current_ch_map = 0x03016f25;
llc_ch_assess_local = 0x03016fa9;
llc_chnl_assess_timer_handler = 0x03017111;
llc_common_enc_change_evt_send = 0x030171f1;
llc_common_enc_key_ref_comp_evt_send = 0x03017271;
llc_common_nb_of_pkt_comp_evt_send = 0x030172ad;
llc_data_ind_handler = 0x03017605;
llc_dft_handler = 0x03017689;
llc_discon_event_complete_send = 0x0301768d;
llc_enc_mgt_ind_handler = 0x030176b1;
llc_env = 0x0400001c;
llc_feats_rd_event_send = 0x030179c1;
llc_common_cmd_status_send = 0x030171d1;
llc_common_cmd_complete_send = 0x030171b1;
llc_length_req_ind_handler = 0x03017d81;
llc_link_sup_to_ind_handler = 0x03017e05;
llc_llcp_recv_ind_handler = 0x03018369;
llc_llcp_rsp_to_ind_handler = 0x030186cd;
llc_ltk_req_send = 0x03018999;
llc_map_update_finished = 0x030189cd;
llc_map_update_ind = 0x03018a61;
llc_pdu_acl_tx_ack_defer = 0x03018ab1;
llc_util_clear_operation_ptr = 0x0301956d;
llc_util_get_nb_active_link = 0x0301966d;
llc_util_set_auth_payl_to_margin = 0x030196b1;
llc_util_update_channel_map = 0x0301970d;
llc_version_rd_event_send = 0x03019721;
llcp_con_param_req_handler = 0x0301989d;
llcp_enc_req_handler = 0x03019e11;
llcp_enc_rsp_handler = 0x03019f1d;
llcp_pause_enc_req_handler = 0x0301a50d;
llcp_ping_rsp_handler = 0x0301ab55;
llcp_start_enc_req_handler = 0x0301abd1;
llcp_unknown_rsp_handler = 0x0301ae55;
lld_core_reset = 0x0301c0b9;
lld_crypt_isr = 0x0301c10d;
lld_evt_channel_next = 0x0301c241;
lld_evt_drift_compute = 0x0301c721;
lld_evt_env = 0x0400013c;
lld_evt_prevent_stop = 0x0301d1f1;
lld_evt_timer_isr = 0x0301e559;
lld_get_mode = 0x0301e69d;
lld_pdu_adv_pack = 0x0301ecb5;
lld_pdu_data_tx_push = 0x0301efd1;
lld_pdu_pack = 0x0301f2d1;
lld_pdu_data_send = 0x0301ef45;
lld_pdu_pop_front = 0x0301f3a3;
lld_pdu_push_back = 0x0301f3b5;
lld_pdu_push_front = 0x0301f3c9;
lld_pdu_tx_flush = 0x0301f819;
lld_pdu_tx_loop = 0x0301f969;
lld_pdu_tx_push = 0x0301fd3d;
lld_sleep_enter = 0x03020151;
lld_sleep_env = 0x04000020;
lld_sleep_init = 0x03020199;
lld_test_mode_rx = 0x030203a9;
lld_test_mode_tx = 0x03020601;
lld_test_stop = 0x0302083d;
lld_util_compute_ce_max = 0x03020995;
lld_util_connection_param_set = 0x03020a41;
lld_util_dle_set_cs_fields = 0x03020a8d;
lld_util_eff_tx_time_set = 0x03020abd;
lld_util_flush_list = 0x03020ae3;
lld_util_get_local_offset = 0x03020b41 ;
lld_util_get_peer_offset = 0x03020b59;
lld_util_get_phys = 0x03020b73;
lld_util_get_tx_pkt_cnt = 0x03020bc3 ;
lld_util_instant_ongoing = 0x03020be7;
lld_util_ral_force_rpa_renew = 0x03020d05;
lld_wlcoex_set = 0x03020da9;
LLM_AA_CT1 = 0x0302bcc0;
llm_ble_ready = 0x03020dc5;
llm_common_cmd_status_send = 0x03020dfd;
llm_dft_handler = 0x030212a1;
llm_ecc_result_ind_handler = 0x030212a5;
llm_le_enh_priv_addr_renew_timer_handler = 0x03021c85;
llm_le_env = 0x04000168;
llm_le_set_host_ch_class_cmd_sto_handler = 0x03021cd1;
llm_local_cmds = 0x0302ba8e;
llm_local_data_len_values = 0x0302ba82;
llm_ral_clear = 0x03021d75;
llm_ral_dev_add = 0x03021dbd;
llm_ral_dev_rm = 0x03021f0d;
llm_ral_update = 0x03022055;
llm_set_adv_data = 0x03022091;
llm_set_scan_rsp_data = 0x0302270d;
llm_state = 0x04000024;
llm_util_apply_bd_addr = 0x03022c81;
llm_util_bd_addr_in_ral = 0x03022ca5;
llm_util_bl_add = 0x03022e91;
llm_util_bl_check = 0x03022f31;
llm_util_bl_rem = 0x03022fad;
llm_util_check_address_validity = 0x03023021;
llm_util_check_evt_mask = 0x03023035;
llm_util_check_map_validity = 0x03023059;
llm_util_get_channel_map = 0x030230c9;
llm_util_get_default_phy = 0x030230d5;
llm_util_get_supp_features = 0x03023105;
llm_util_set_public_addr = 0x03023115;
llm_wl_clr = 0x03023129;
nvds_del = 0x030254c5;
nvds_env = 0x04000384;
nvds_get = 0x0302559d;
nvds_init = 0x03025621;
nvds_lock = 0x030256f5;
nvds_put = 0x03025849;
fw_nvds_api = 0x0302c59c;
rf_init = 0x03025a69;
rwble_sleep_check = 0x03025be1;
rwip_coex_cfg = 0x04000038;
rwip_env = 0x040003b0;
rwip_prevent_sleep_clear = 0x03025d49;
rwip_prevent_sleep_set = 0x03025d8d;
rwip_priority = 0x04000034;
rwip_rf = 0x04000044;
rwip_schedule = 0x03025e29;
rwip_wakeup_delay_set = 0x030260a1;
rwip_wakeup_end = 0x030260e1;
set_32k_ppm = 0x0302613d;
unloaded_area_init = 0x0302abdd;
