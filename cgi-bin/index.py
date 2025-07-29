#!/usr/bin/python
import pygetwindow as gw

def get_open_windows_pygetwindow():
	open_windows = gw.getAllTitles()
	return [title for title in open_windows if title] # Filter out empty titles

if __name__ == "__main__":
	print("Content-Type: text/plain\n")


	open_apps = get_open_windows_pygetwindow()
	for app_title in open_apps:
		if ( app_title.find('Google') != -1 and app_title.find('Meet') != -1 ):
			print("Meet is Running")
			break
