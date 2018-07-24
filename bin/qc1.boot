#! /bin/sh

swipl --traditional -x /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin/qc1.boot.po -F none -f none -t halt -g "main(['$1'])"
