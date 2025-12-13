print("[ OK ]: starting build dltsh")
print("[ OK ]: fast = true")
print("[ OK ]: compiling source code")
local STATUS_VERSION = os.getenv("STATUS_VERSION") or ""
local STATUS_OS = os.getenv("STATUS_OS") or ""

print(string.format('status: version=v.0.0.0.12-c %s', STATUS_VERSION))
print(string.format('status: OS=OpenDelta Linux %s', STATUS_OS))

local home = os.getenv("HOME") or ""
local workdir = home .. "/OpenDelta/shell/"
local gcc_cmd = "clang term.c commands.c files.c dltsh_base.c simple_comms.c -o term"
local term_path = workdir .. "./term"
local chmod_cmd = "chmod +x " .. term_path

local function run(cmd, allow_fail)
  io.write("[ OK ]:  " .. cmd .. "\n")
  local res, reason, code = os.execute(cmd)
  if type(res) == "number" then
    if res ~= 0 and not allow_fail then
      error("Command failed with status: " .. tostring(res))
    end
    return res
  else
    local ok = (res == true) or (reason == "exit" and code == 0)
    if not ok and not allow_fail then
      error(string.format("Command failed: %s (res=%s reason=%s code=%s)", cmd, tostring(res), tostring(reason), tostring(code)))
    end
    return code or (ok and 0 or 1)
  end
end

local ok_dir = lfs or nil
local chdir_ok, chdir_err = pcall(function() return os.execute("cd " .. workdir) end)
local success, msg = pcall(function() return os.execute("") end)
local function change_dir(path)
  local ok, lfs = pcall(require, "lfs")
  if ok and lfs.chdir then
    local res, err = lfs.chdir(path)
    if not res then error("chdir failed: " .. tostring(err)) end
    return
  end
  error("LuaFileSystem (lfs) not available; the script will run commands with explicit cd")
end

local has_lfs, lfs = pcall(require, "lfs")
if has_lfs and lfs.chdir then
  local okc, err = lfs.chdir(workdir)
  if not okc then error("Failed to chdir: " .. tostring(err)) end
  run(gcc_cmd)
  run("./bin/term", true)
  run("chmod +x bin/term")
else
  run("cd " .. workdir .. " && " .. gcc_cmd)
  run("cd " .. workdir .. " && ./bin/term", true)
  run("cd " .. workdir .. " && " .. chmod_cmd)
end
