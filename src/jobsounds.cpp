//(AUTO-GENERATED FROM "lua/jobsounds.lua", DO NOT EDIT THIS FILE)
const char* JOBSOUNDS_SOURCE =
"-- Adds job sounds.\n"
"--@ module = true\n"
"\n"
"--[====[\n"
"\n"
"Job sounds\n"
"===========\n"
"Connects to a socket (tcp), checks the current job of dwarves and sends messages\n"
"\n"
"]====]\n"
"\n"
"local scriptName = 'jobsounds'\n"
"\n"
"local function initSocket()\n"
"	socket = tcp:connect('127.0.0.1', 56730)\n"
"end\n"
"\n"
"local function start()\n"
"	luasocket = require(\"plugins.luasocket\")\n"
"	tcp = luasocket.tcp\n"
"	dfhack.println(scriptName..\" connecting...\")\n"
"	socket = nil;\n"
"	pcall(initSocket)\n"
"	if (socket ~= nil) then\n"
"		dfhack.println(scriptName..\" connected\")\n"
"		stop = false\n"
"		timeLastSend = os.time()\n"
"		loop()\n"
"	else\n"
"		dfhack.println(scriptName..\" could not connect\")\n"
"	end\n"
"end\n"
"\n"
"local function send(msg)\n"
"	if (pcall(socket.send, socket, msg) == true) then\n"
"		timeLastSend = os.time()\n"
"	else\n"
"		stop = true\n"
"	end\n"
"end\n"
"\n"
"local function triggerJobSound(unit, jobType)\n"
"	if (socket ~= nil) then\n"
"		if (\n"
"		    df.global.window_z == unit.pos.z and\n"
"			df.global.window_x < unit.pos.x and\n"
"			df.global.window_x+90 > unit.pos.x and\n"
"			df.global.window_y < unit.pos.y and\n"
"			df.global.window_y+60 > unit.pos.y\n"
"		) then\n"
"			send(unit.id .. \" \" .. jobType .. \"\\0\")\n"
"		end\n"
"	end\n"
"end\n"
"\n"
"local function handleDwarf(unit)\n"
"	if (unit.job.current_job ~= nil) then\n"
"		local jobPos = unit.job.current_job.pos\n"
"		local dx = math.abs(jobPos.x-unit.pos.x)\n"
"		local dy = math.abs(jobPos.y-unit.pos.y)\n"
"		local dz = math.abs(jobPos.z-unit.pos.z)\n"
"		if (dx <= 1 and dy <= 1 and dz <= 1) then\n"
"			triggerJobSound(unit, unit.job.current_job.job_type)\n"
"		end\n"
"	end\n"
"end\n"
"\n"
"local function checkDwarves()\n"
"	for k,unit in ipairs(df.global.world.units.active) do\n"
"		if (dfhack.units.isDwarf(unit)) then\n"
"			handleDwarf(unit)\n"
"		end\n"
"	end\n"
"end\n"
"\n"
"function loop()\n"
"	if (os.time() - timeLastSend > 2) then\n"
"		send(\"null\\0\")\n"
"	end\n"
"\n"
"	if (stop == true) then\n"
"		dfhack.println(scriptName..\" stopped\")\n"
"		return\n"
"	end\n"
"\n"
"	if (df.global.pause_state == false) then\n"
"		checkDwarves()\n"
"	end\n"
"\n"
"	dfhack.timeout(15, 'ticks', loop)\n"
"end\n"
"\n"
"start()\n";
