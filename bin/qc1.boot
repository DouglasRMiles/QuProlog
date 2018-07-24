#! /bin/sh

swipl --traditional -x /home/pjr/research/qp_dev/rel/qp10.1/bin/qc1.boot.po -F none -f none -t halt -g "main(['$1'])"
