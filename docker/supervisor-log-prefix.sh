#!/bin/bash

# Get prefix from SUPERVISOR_PROCESS_NAME environment variable
printf -v PREFIX "%-10.10s" "${SUPERVISOR_PROCESS_NAME}"

# Prefix stdout and stderr
exec 1> >( perl -ne '$| = 1; print "'"${PREFIX}"' | $_"' >&1)
exec 2> >( perl -ne '$| = 1; print "'"${PREFIX}"' | $_"' >&2)

exec "$@"
