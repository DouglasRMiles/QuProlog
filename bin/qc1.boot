#! /bin/sh

swipl --traditional -x /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/qc1.boot.po -F none -f none -t halt -g "main(['$1'])"
