#!/bin/bash
# Move this file wherever it's configured in the autostart in config.h
# Dependencies: thunar, chromium, alacritty, brightnessctl, xinput, fonts awesome

	status(){

		# Temperature:
		cpu_temp=$(sed 's/000$//' /sys/class/thermal/thermal_zone7/temp)
		#cpu_temp=$(sensors coretemp-isa-0000 | grep Package); cpu_temp=${cpu_temp:16:2}

		# CPU
		cpu=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" |awk '{print 100 - $1"%"}')
		cpu=" $cpu"


		if [ $cpu_temp -gt 70 ]; then
			cpu_temp=" $cpu_temp";
		else
			cpu_temp=" $cpu_temp";
		fi

		
		# Battery		
		capacity=$(cat /sys/class/power_supply/BAT0/capacity) 
		if [ $capacity -gt 90 ]; then
			capacity="  $capacity"	
		elif [ $capacity -lt 30 ]; then
			capacity="  $capacity"	
		else
			capacity="  $capacity"	
		fi

		status=$(cat /sys/class/power_supply/BAT0/status)
		if [ $status = 'Discharging' ]; then
			status="  "
		elif [ $status = 'Full' ]; then
			status="  "
		elif [ $status = 'Charging' ]; then
			status="  "
		fi
 

		# Backlight
		brightness=" $(( `cat /sys/class/backlight/intel_backlight/brightness` * 100 / `cat /sys/class/backlight/intel_backlight/max_brightness` ))";


		# Date and time
		date="  $( date '+%a %d/%m %H:%M' )";

		# Volume
		is_mute=$(pactl get-sink-mute @DEFAULT_SINK@)
		if [ "$is_mute" = "Mute: yes" ]; then 
			is_mute=1; 
		else
			is_mute=0;
		fi

		long_volume=$(pactl get-sink-volume @DEFAULT_SINK@);
		
		if [ $is_mute = 1 ]; then
			short_volume="  0";
		else
			short_volume=" ${long_volume:28:4}";
		fi

		# Keyboard layout
		layout_num=$(xset -q|grep LED| awk '{ print $10 }')
		kb_layout=" "

		if [ $layout_num -lt 10 ]; then
			kb_layout="$kb_layout us"
		elif [ $layout_num -lt 1010 ]; then
			kb_layout="$kb_layout es"
		fi

		
		# Weather
		#LOCATION=Mendoza
		#weather=$(curl -s wttr.in/$LOCATION?format=1)

		
		echo "$short_volume | $brightness | $capacity - $status | $kb_layout | $cpu | $cpu_temp | $date";

	}

while true; do

	xsetroot -name "$(status)"

	sleep 12
done
