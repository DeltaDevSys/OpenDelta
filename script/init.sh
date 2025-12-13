cd ~/OpenDelta/shell/
echo "✓starting OS..."
$STATUS_BOOTING
$STATUS_VERSION
$STATUS_OS
echo "✓status: version=v.0.0.0.12-c $STATUS_VERSION"
echo "✓status: booting=true $STATUS_BOOTING"
echo "✓status: OS=OpenDelta Linux $STATUS_OS"
clang term.c commands.c files.c dltsh_base.c simple_comms.c -o term
./term
chmod +x ./term
echo "✓ending os"
