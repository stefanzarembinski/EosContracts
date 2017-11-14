```
EOSIO_INSTALL_DIR="/mnt/hgfs/Workspaces/EOS/eos" &&\
workspaceDir="/mnt/hgfs/Workspaces/EOS/EosContracts/eoscLib/eosContract"

contractSrcDir=${workspaceDir} &&\
source /mnt/hgfs/Workspaces/EOS/eoscBash/eoscBash $EOSIO_INSTALL_DIR

eosc buildContract ${contractSrcDir}/contract.cpp
eosc wallet create
eosc wallet unlock
eosc wallet import $initaPrivKey
eosc set contract ${initaAccount} ${contractSrcDir}/contract.wast ${contractSrcDir}/contract.abi

jq '.processed.messages' <<< "$contractSet"

eosc push message ${initaAccount} transfer '{"from":"currency","to":"inita","amount":50}' --scope initc
```