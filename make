#!/bin/bash

set -x

#bc_server
clear; rm -frv write_to_db_linsert.o; g++-7 -O3 -fPIC -Wall -c write_to_db_linsert.cpp; rm -frv check_block_exists.o; g++-7 -O3 -fPIC -Wall -c check_block_exists.cpp ;rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c  read_config_file.cpp;rm -frv filter_pure_bc_block_for_peer.o; g++-7 -O3 -fPIC -Wall -c filter_pure_bc_block_for_peer.cpp ;rm -frv send_block_to_reachable_peers.o; g++-7 -O3 -fPIC -Wall -c send_block_to_reachable_peers.cpp ;rm -frv filter_pure_bc_block.o; g++-7 -O3 -fPIC -Wall -c  filter_pure_bc_block.cpp ;rm -frv compare_hashes_single_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_hashes_single_peer_local.cpp;rm -frv  validate_chains_peer_local_with_remote_ip_only.o; g++-7 -O3 -fPIC -Wall -c  validate_chains_peer_local_with_remote_ip_only.cpp ;rm -frv send_peer_local_chain_longer_and_send_blocks.o; g++-7 -O3 -fPIC -Wall -c send_peer_local_chain_longer_and_send_blocks.cpp  ;rm -frv hasher.o; g++-7 -O3 -fPIC -Wall -c hasher.cpp ;rm -frv rpoplpush_redis.o; g++-7 -O3 -fPIC -Wall -c rpoplpush_redis.cpp; rm -frv compare_hashes_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_hashes_peer_local.cpp ;rm -frv compare_blocks_peer_local.o; g++-7 -O3 -fPIC -Wall -c compare_blocks_peer_local.cpp; rm -frv read_peer_single_block.o; g++-7 -O3 -fPIC -Wall -c read_peer_single_block.cpp ;rm -frv validate_chains_peer_local.o; g++-7 -O3 -fPIC -Wall -c  validate_chains_peer_local.cpp ;rm -frv write_to_db.o; g++-7 -O3 -fPIC -Wall -c write_to_db.cpp ;rm -frv read_peer_blocks.o; g++-7 -O3 -fPIC -Wall -c  read_peer_blocks.cpp ; rm -frv read_peer_lists.o; g++-7 -O3 -fPIC -Wall -c read_peer_lists.cpp; rm -frv read_all_chains_from_db.o; g++-7 -O3 -fPIC -Wall -c read_all_chains_from_db.cpp; rm -frv bc_server.o; g++-7 -O3 -fPIC -Wall -c bc_server.cpp; rm -frv bc_server; g++-7 -O3 -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -lpthread -o bc_server bc_server.o read_all_chains_from_db.o read_peer_lists.o read_peer_blocks.o write_to_db.o validate_chains_peer_local.o read_peer_single_block.o compare_blocks_peer_local.o compare_hashes_peer_local.o rpoplpush_redis.o hasher.o send_peer_local_chain_longer_and_send_blocks.o validate_chains_peer_local_with_remote_ip_only.o compare_hashes_single_peer_local.o filter_pure_bc_block.o send_block_to_reachable_peers.o filter_pure_bc_block_for_peer.o read_config_file.o check_block_exists.o write_to_db_linsert.o -static-libstdc++ ;date

#blockchain_daemon
rm -frv create_gpg_encryption.o; g++-7 -O3 -fPIC -Wall -c create_gpg_encryption.cpp;rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c  read_config_file.cpp;rm -frv get_last_block.o; g++-7 -O3 -fPIC -Wall -c get_last_block.cpp ;rm -frv send_block_to_server.o; g++-7 -O3 -fPIC -Wall -c send_block_to_server.cpp ; rm -frv insrert_bc_to_db.o; g++-7 -O3 -fPIC -Wall -c insrert_bc_to_db.cpp; rm -frv create_gpg_signature.o; g++-7 -O3 -fPIC -Wall -c create_gpg_signature.cpp ;rm -frv read_previous_chains.o; g++-7 -O3 -fPIC -Wall -c read_previous_chains.cpp ;rm -frv timestamp.o; g++-7 -O3 -fPIC -Wall -c timestamp.cpp ;rm -frv blockchain_daemon.o; g++-7 -Wall -O3 -c blockchain_daemon.cpp; rm -frv hasher.o; g++-7 -O3 -fPIC -Wall -c hasher.cpp; rm -frv blockchain; g++-7 -O3 -fPIC -Wall -ltls -lssl -lcrypto -lgpgme -o blockchain blockchain_daemon.o hasher.o timestamp.o read_previous_chains.o create_gpg_signature.o insrert_bc_to_db.o send_block_to_server.o get_last_block.o read_config_file.o create_gpg_encryption.o -static-libstdc++ ;date;

#sap_blockchain_connector
rm -frv read_config_file.o; g++-7 -O3 -fPIC -Wall -c read_config_file.cpp ;rm -frv sap_bcc; g++-7 -O3 -fPIC -Wall sap_bcc.cpp -o sap_bcc read_config_file.o -static-libstdc++; date;

#config
echo "bc_server = 127.0.0.1" >> bc.cfg
echo "bc_server port = 8888" >> bc.cfg
echo "redis server = 127.0.0.1" >> bc.cfg
echo "redis port = 6379" >> bc.cfg

#peer lists
echo "127.0.0.1" >> peer_list.cfg

