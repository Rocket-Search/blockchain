# blockchain
blockchain;  Distributed Ledger List (SAP ERP 6.0 FI Connector)



first "read the manual" .

Than just copy the bc_server to your desired folder an start it.

you can access and generate blocks to the chain with the "blockchain" binary .

If you want to connect a SAP System to the blockchain network, implement the
"sap_bcc" binary to your SAP System.

if you need help , don't hesitate to contact me : 
software.moore@gmail.com

You can also download it at http://rocketsearch.ddns.net:8081/bc.tar.gz

More Information:
http://rocketsearch.ddns.net/index.php/en/blockchain

##################

technical overview

All software components are written in C++ compiled with g++-7 (SUSE Linux) 7.3.1 20180307 [gcc-7-branch revision 258314]

Blockchain Generator:
The raw data will be transmitted via ARGV to the blockchain genereator.
Further the exact timestamp will be keept up to the nanosecond range (tv_nsec)
Than the next free block number in the chain will be determined. I use the TCP socket API with
TLS (LibreSSL) encryption for the block number determintaion in the chain peer-to-peer network.
The determintaion of the block number will also check the validation of the last block and in 
the same time the prevoius hash will be requested.
From the transaction raw data, plus timestamp, plus blocknumber, plus previous hash 
the transaction hash will be generated. It consits by a SHA512 hash provide by the SSL API (LibreSSL).
Than the hash will be encrypted with the GnuPG API (gpgme) and also a GPG signture will be created.
From this it is possible to determine which server has generated the block and the hash of the block is cryptographically secured against manipulation .
The GPG signature consists of an AES256 key that generates a SHA512 long signature (base64 format).
After the generation of the new block, the block is sent to the blockchain server .
The transmission uses the TLS transport layer encryption . The encryption use the following
algorithm "ECDHE-RSA-AES256-GCM-SHA512" and "Perfect Forward Secrecy" based on the TLS protocoll 1.2 .
The server certificate has a keys size from 16384 bytes .
After the block has been sent to the blockchain server, it is sent (also using TLS) to the available peers .
At leats 5 peers must confirm the vaildaitaion of the block and when they give the "OK" the block will be
included in the chain .

Blockchain Server:
The blockchain server checks when starting whether all the peers known to him are available and whether the various peers are valid, or
the blockers of the peers match the chain of the local server .
The communication was encrypted using TLS 1.2 "ECDHE-RSA-AES256-GCM-SHA512".
The server certificate has a 16384 bytes long key.
The blocks are stored in the in-memory NoSQL Database redis.

SAP Blockchain Connector:
The SAP_BC stores the data encrypted with GPG (AES256) locally on a RAM disk.
Via SSH, the SAP_BC can address the blockchain generator and send the data encrypted over the network.
therefore a user authentication takes place at Blockchain Gernertaor.

Network API:
SHA512 transaction hash
GPG encyrption ang signature with AES256 and SHA512 encryption, for each block
Network transport encryption with TLS 1.2 and ECDHE-RSA-AES256-GCM-SHA512
SAP system Blockchain Connector for SAP ERP 6.0 (FI_CO etc.)
Timestamp for the transaction in the nanosecond range
Using redis in-memory database
Using RAM disks
Distribute the blocks in a Perr-to-Peer network
Thread based TCP connection management
Cyclic validation of the whole chain on all peers.
#################

if you ask me, I will give you the source code
