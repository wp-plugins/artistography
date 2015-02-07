// Use these Javascript variables to control the applet parameters

var numkeys 			= 1; // The number of keys you have
var keys= new Array(numkeys);

// Enter you keys here in the following form, starting with key[0], key[1], key[2], etc...
 
keys[0]				= ""; 

// Un-comment the folowing lines to add additional keys

//keys[1]				= ""; 
//keys[2]				= "";


// Connection related values
		
var server 			= "";  //host name or IP of FTP server
var port 			= "";  //The port number of the FTP server. Default 21
var user 			= "";  //The username for the FTP server account
var pass 			= "";  //The password for the FTP server account
var autoconnect			= "";  //If true, will connect based on above settings and hide connect/disconnect buttons.  Default false
var autoreconnect		= "";  //If true, will not prompt for reconnect.  Default true
var passive 			= "";  //Toggle passive or active connection.  Default true
var encrypt			= "";
var ek				= "";
var connecttimeout		= "";  //value in ms for connection attempt. Default 20000
var sotimeout			= "";  //value in ms to wait for read before timing out. Default -1 (no timeout)
var waitRetry 			= "";  //value in ms to wait before attempting reconnect. Default 3000
var maxRetries 			= "";  //number of times to attempt retry. Default 1
var bufSizeGet 			= "";  //This value specifies the size of the transfer buffer UnlimitedFTP will use when downloading files
var bufSizePut 			= "";  //This value specifies the size of the transfer buffer UnlimitedFTP will use when uploading files
var useSerfo			= "";  //see documentation.  Default false
var SerfoLocation		= "";  //see documentation.  Default not used
var enableHTTPResume 		= "";  //see documentation; requires useSerfo to be true
var characterEncoding 		= "";

// Proxy related settings for IE only

var autodetectproxy		= "";  //If true, automatically attempt to detect IE's Proxy setup.  Default false
var socksproxy			= "";  //If true, use the SOCKS proxy server and port specified below.  Default false
var socksProxyHost		= "";  //SOCKS proxy server location
var socksProxyPort		= "";  //SOCKS proxy server port
var ftpproxy			= "";  //If true (and socksproxy false), use FTP proxy specified below.  Default false
var ftpProxyHost		= "";  //FTP proxy server location
var ftpProxyPort		= "";  //FTP proxy server port


// Functionallity related values

var ascbin			= "";  //Default transfer mode (asc, bin, auto).  Default bin
var asciiextensions		= "";  //Transfer all the files with these extensions in Ascii Mode (comma delimited list) if ascbin is auto
var extensions			= "";  //Only files with these extensions will be displayed/affected by UnlimitedFTP
var exclude			= "";  //exclude files or directories matching pattern (comma delimited list)
var invertExclude 		= "";  //If true, change exclude list to an include-only list.  Default false
var lockinitialdir		= "";  //If true, lock user to initial directory and its subdirectories.  Default false
var localdir 			= "";  //switch to this local directory when UFTP loads (<directory>, HOME, DESKTOP, ROOT)
var remotedir 			= "";  //switch to this directory after login.  Eg "/initialdir"
var createdirectoryonconnect	= "";  //create this directory after login.  Eg "/mydirectory"
var enableCookies		= "";  //If true, UFTP will store cookies to remember the last site and username.  Default true
var doubleClickTransfer		= "";  //If true, double-clicking file will initiate transfer. Default true
var enablerightclick		= "";  //If set to false, right-click menu disabled for end user.  Default true
var enablekeyboardshortcuts	= "";  //If changed to false, keyboard shortcuts disabled for end user.  Default true
var confirmoverwrite		= "";  //If true, prompt for overwrite if file exists.  Default true
var confirmTransfer 		= "";  //If true, prompt before each upload or download.  Default false
var syncpriority		= "";  //When using Sync function, this parameter determines which is master (local, remote) Default local
var incremental			= "";  //If true, files that have not been modified locally will not be transferred.  Default false
var incdatetime			= "";  //If true, use time and date to determine file modification.  Default false
var timezonecomp		= "";  //A value (in minutes) for calculating time zone difference.  Default 0
var selectalllocal		= "";  //If true, all files in initial local directory will be selected when UnlimitedFTP initializes.   Defalt false
var selectallremote		= "";  //If true, all files in initial remote directory will be selected after connection.  Default false
var selectfileremote    	= "";  //Specified filename will be selected after connection.  Default none
var autoupload			= "";  //If selectalllocal variable is used, automatically upload files after connection.  Default false
var autodownload		= "";  //If selectallremote/selectfileremote are used, automatically download these after connection.  Default false
var autoallo			= "";  //If true, ALLO command sent to server.  Not all FTP servers implement ALLO.  Default false
var hostsAllowed		= "";  //List of URLs to limit hosts and IPs allowed for connection.  Default no limitation
var totalProgress		= "";  //If false, show progress of individual files instead of entire upload.  Default true
var enableResume 		= "";  //(true, false, auto).  Prompt user to attempt resume.  Default true
var deleteoncancel		= "";  //If true, partial transfers deleted on cancel.  Default true
var customFileOptions 		= "";  //Customize right-click file options.  See documentation
var customDirOptions 		= "";  //Customize right-click directory options.  See documentation
var sendLogsToURL 		= "";  //make HTTP POST to specified URL with FTP log.   Default none
var preserveModificationTime 	= "";  //if true, source time and date is written to the destination.  Default false
var removeAccentsAndQuotes	= "";  //if true, accented letters and quotation marks are removed from filename at destination.  Default false
var removeSpaces		= "";  //if true, all spaces in the filename are removed at destination.  Default false
var helplocation	    	= "documentation.html";  //Specify help file location.


// Values that effect the color of the client

var background 			= "";  //default 255,255,255
var buttonTextColorOnMouseOver	= "";  //default 255,255,255	
var buttonTextColor		= "";  //default 0,0,0
var buttonColorOnMouseOver	= "";  //default 10,50,10
var buttonbackground		= "";  //default 81,132,81
var headerTextColor		= "";  //default 0,0,255
var headerBackgroundColor	= "";  //default same as background variable
var drivesForegroundColor 	= "";  //default 0,0,0
var drivesBackgroundColor 	= "";  //default 255,255,255
var ascBinTextColor 		= "";  //default 0,0,0


// values that effect the interface layout of the client

var width			= "640";  //Integer value in pixels
var height			= "480";  //Integer value in pixels
var language 			= "";  //See documentation
var classicfilelist		= "";  //If true, use default VM file list. Default false
var useToolbar			= "";  //Set to false to revert to legacy GUI. Default true
var useBottomToolbar		= "";  //Set to false to revert to legacy GUI. Default true
var LocalOptions		= "";  //Enable or disable local option buttons. Set to false to hide all.  Default all visible
var RemoteOptions		= "";  //Enable or disable remote option buttons. Set to false to hide all.  Default all visible
var remoteheader		= "";  //Specify text to show above remote list.  Default to hostname/IP
var stretchButtons		= "";  //For legacy GUI only. Stretch function buttons to fill empty space.  Default true
var display			= "";  //If false, hide the FTP message display area. Default true
var showsizeanddate		= "";  //If true, show details next to filename. Default false
var showascbin			= "";  //Set false to hide ascii/binary radio button on GUI. Default true
var showhelpbutton		= "";  //Set false to hide help button on GUI. Default true
var showputbutton		= "";  //Set false to hide upload button on GUI. Default true
var showgetbutton		= "";  //Set false to hide download button on GUI. Default true
var showsyncbutton		= "";  //Legacy GUI only.  Set false to hide sync button on GUI. Default true
var showaboutbutton		= "";  //Set false to hide help button on GUI. Default true
var showconnectbutton 		= "";  //Set false to hide connect button on GUI. Default true
var showdisconnectbutton 	= "";  //Set false to hide disconnect button on GUI. Default true
var showlocallist		= "";  //Set false to hide local file list as well as local buttons.  Default true.
var showremotelist		= "";  //Set false to hide remote file list as well as remote buttons.  Default true.
var showSizeInKB		= "";  //Set true to display file size in KB instead of bytes.  Default false
var showlocaladdressbar		= "";  //Set false to hide local directory path field.  Default true
var showremoteaddressbar	= "";  //Set false to hide remote path field.  Default true
var showFileInfoBar 		= "";  //If true, show name, date, and size of file below local or remote list.  Default false
var showStatusBar 		= "";  //If true, display a status bar for connectivity and security.  Default false
var showTree			= "";  //If false, only content of current directory is shown.  Default true


// some customizable error pages

var rejectPermissionURL = "rejectPerms.html";  //User has rejected security certificate or has not trusted applet
var errNavWin 		= "errNavWin.html";  //Windows Navigator version is not sufficient
var errIEWin 		= "errIEWin.html";  //Windows Internet Explorer version is not sufficient
var errOperaWin		= "errOperaWin.html";  //Windows Opera version is not sufficient
var errIEWinVM		= "errIEWinVM.html";  //Windows IE Java version is not sufficient
var errNavUnix		= "errNavUnix.html";  //Unix Navigator version is not sufficient
var errIEMac		= "errIEMac.html";  //Mac Internet Explorer version is not sufficient
var errNavMac		= "errNavMac.html";  //Mac navigator version is not sufficient

//*************************************************************************************** //
// ********** DO NOT EDIT BELOW THIS POINT UNLESS YOU KNOW WHAT YOU ARE DOING!  ********* //
//*************************************************************************************** //
	var n;

        var agt=navigator.userAgent.toLowerCase();

        // detect browser version
        // Note: On IE5, these return 4, so use is_ie5up to detect IE5.
        var is_major = parseInt(navigator.appVersion);
        var is_minor = parseFloat(navigator.appVersion);

        // *** BROWSER TYPE ***
        var is_nav  = ((agt.indexOf('mozilla')!=-1) && (agt.indexOf('spoofer')==-1)
                    && (agt.indexOf('compatible') == -1) && (agt.indexOf('opera')==-1)
                    && (agt.indexOf('webtv')==-1));

	var is_opera = (agt.indexOf('opera')!=-1);
	var is_safari = (agt.indexOf('safari')!=-1);
	var is_konqueror = (agt.indexOf('konqueror')!=-1);
	var is_opera6up = (is_opera && (is_major >= 6));
        var is_nav4up = (is_nav && (is_major >= 4));
	var is_nav6up = (is_nav && (is_major >= 6));
        var is_ie   = (agt.indexOf("msie") != -1);
        var is_ie3  = (is_ie && (is_major < 4));
        var is_ie4  = (is_ie && (is_major == 4) && (agt.indexOf("msie 5.0")==-1) );
        var is_ie5  = (is_ie && (is_major == 4) && (agt.indexOf("msie 5.0")!=-1) );
        var is_ie5up  = (is_ie  && !is_ie3 && !is_ie4);
        var is_firefox =  (agt.indexOf("firefox") != -1);

	// *** PLATFORM ***
        var is_win   = ( (agt.indexOf("win")!=-1) || (agt.indexOf("16bit")!=-1) );
	var is_mac   = (agt.indexOf("mac")!=-1);
        var is_sun   = (agt.indexOf("sunos")!=-1);
        var is_irix  = (agt.indexOf("irix") !=-1);    
        var is_hpux  = (agt.indexOf("hp-ux")!=-1);
        var is_aix   = (agt.indexOf("aix") !=-1);     
        var is_linux = (agt.indexOf("inux")!=-1);
        var is_sco   = (agt.indexOf("sco")!=-1) || (agt.indexOf("unix_sv")!=-1);
        var is_unixware = (agt.indexOf("unix_system_v")!=-1);
        var is_mpras    = (agt.indexOf("ncr")!=-1);
        var is_reliant  = (agt.indexOf("reliantunix")!=-1);
        var is_dec   = ((agt.indexOf("dec")!=-1) || (agt.indexOf("osf1")!=-1) ||
               (agt.indexOf("dec_alpha")!=-1) || (agt.indexOf("alphaserver")!=-1) ||
               (agt.indexOf("ultrix")!=-1) || (agt.indexOf("alphastation")!=-1));
        var is_sinix = (agt.indexOf("sinix")!=-1);
        var is_freebsd = (agt.indexOf("freebsd")!=-1);
        var is_bsd = (agt.indexOf("bsd")!=-1);
        var is_unix  = ((agt.indexOf("x11")!=-1) || is_sun || is_irix || is_hpux ||
                     is_sco ||is_unixware || is_mpras || is_reliant ||
                     is_dec || is_sinix || is_aix || is_linux || is_bsd || is_freebsd);
	
	function isMacClassic() {
		return (is_mac && !isMacX());
	}

	function isMacX() {
		if (isMacJaguar()) return true;	
		if (agt.indexOf("omniweb") != -1) return true;			
 		for (var i = 0; i < navigator.plugins.length; i++) {
  			if (navigator.plugins[i].name.indexOf("OJI") > -1) return true;	
			if (navigator.plugins[i].name.indexOf("Default Plugin Carbon.cfm") > -1) return true;			
 		}  	
		return false;		
	}

	function isMacJaguar() {
		return (is_mac && javaPlugin()); // we know java plugin means 10.2 or higher
	}

	function appletWillRun() {
        	if (is_ie4 || is_ie5up || (is_nav4up && is_minor >= 4.08) || is_opera6up || is_konqueror || isMacJaguar())                  
			return true;           
        	return false;
	}
	

	function javaPlugin() {
		
		if (is_safari || is_opera6up || is_firefox || is_konqueror) return true;   // we know safari and opera use java plugin
 		for (var i = 0; i < navigator.plugins.length; i++) {
  			if (navigator.plugins[i].name.indexOf("Java Plug-in") > -1) return true;
	        if (navigator.plugins[i].name.indexOf("Java Embedding Plug") > -1) return true;
 		} 
		return false;		
	}

	function mrj()  {
		if (isMacX()) return true;	
 		for (var i = 0; i < navigator.plugins.length; i++) {
  			if (navigator.plugins[i].name.indexOf("MRJ") > -1) return true;			
 		} 
		return false;
	}



	// The following script will detect weather MAC or PC version of the applet should be started 
	// and set up the apropriate jar file

	var jar = "/wp-content/plugins/artistography/ftp/unlimitedftp.jar";
	var classname = "unlimited.ftp.UnlimitedFTPPlugin";


	
	var netmac=0;			// netmac = 0 means it is either Mac/IE or non-Mac or Mac Jaguar 
	if (is_nav && is_minor < 6 && !isMacJaguar()) {	
		if (javaPlugin() || mrj()) {	 		
 			var netmac=1;	// netmac = 1 means this is Mac/Netscape and Netscape is older than 4.76					
		} else if (isMacClassic() && !mrj()) { 
			var netmac=2;	// this is Mac/Netscape earlier than 4.76 w/o MRJ Plugin
		}	
	}

	if (netmac == 0) {  // This is non-Mac or Mac with IE 
   	   if ((!navigator.javaEnabled()) && !is_mac && (navigator.appName=="Netscape") && (parseInt(navigator.appVersion)>=5)){
      		document.write("<p><b>Error Java Disabled!</b></p>");
      		document.write("<p>To enable Java in Netscape 6:</p>");
      		document.write("<p>- Go to Edit - Preferences<br>- Click on Advanced<br>- Check \"Enable Java\"<br>- Reload this page</p>");
           }

	   if (appletWillRun()) {  		  		
		if (is_ie && !isMacJaguar())
			document.write("<OBJECT name=UnlimitedFTP classid='clsid:8AD9C840-044E-11D1-B3E9-00805F499D93' height="+height+" width="+width+"'>");
		else
			document.write("<APPLET name=UnlimitedFTP code="+classname+".class height="+height+" archive="+jar+" width="+width+" MAYSCRIPT VIEWASTEXT>");
          	document.write("<param name='archive' value='"+jar+"'>");
          	document.write("<param name='code' value='"+classname+".class'>");
		document.write("<PARAM NAME='type' VALUE='application/x-java-applet;version=1.3'>");
  		document.write("<PARAM NAME='server' VALUE='"+server+"'>");
  		document.write("<PARAM NAME='port' VALUE='"+port+"'>");
  		document.write("<PARAM NAME='pass' VALUE='"+pass+"'>");
  		document.write("<PARAM NAME='user' VALUE='"+user+"'>");
  		document.write("<PARAM NAME='autoconnect' VALUE='"+autoconnect+"'>");	
		document.write("<PARAM NAME='autoreconnect' VALUE='"+autoreconnect+"'>");
		document.write("<PARAM NAME='ascbin' VALUE='"+ascbin+"'>");	
		document.write("<PARAM NAME='showascbin' VALUE='"+showascbin+"'>");		
  		document.write("<PARAM NAME='asciiextensions' VALUE='"+asciiextensions+"'>");
  		document.write("<PARAM NAME='passive' VALUE='"+passive+"'>");
  		document.write("<PARAM NAME='extensions' VALUE='"+extensions+"'>");  		
		document.write("<PARAM NAME='exclude' VALUE='"+exclude+"'>"); 		
  		document.write("<PARAM NAME='lockinitialdir' VALUE='"+lockinitialdir+"'>"); 
		document.write("<PARAM NAME='remotedir' VALUE='"+remotedir+"'>"); 
		document.write("<PARAM NAME='localdir' VALUE='"+localdir+"'>"); 	
		document.write("<PARAM NAME='enableCookies' VALUE='"+enableCookies+"'>"); 	
		document.write("<PARAM NAME='doubleClickTransfer' VALUE='"+doubleClickTransfer+"'>"); 	
		document.write("<PARAM NAME='syncpriority' VALUE='"+syncpriority+"'>"); 
		document.write("<PARAM NAME='incremental' VALUE='"+incremental+"'>");
		document.write("<PARAM NAME='incdatetime' VALUE='"+incdatetime+"'>");
		document.write("<PARAM NAME='timezonecomp' VALUE='"+timezonecomp+"'>");
		document.write("<PARAM NAME='background' VALUE='"+background+"'>");
		document.write("<PARAM NAME='buttonTextColorOnMouseOver' VALUE='"+buttonTextColorOnMouseOver+"'>");
		document.write("<PARAM NAME='buttonTextColor' VALUE='"+buttonTextColor+"'>");
		document.write("<PARAM NAME='buttonColorOnMouseOver' VALUE='"+buttonColorOnMouseOver+"'>");
		document.write("<PARAM NAME='headerTextColor' VALUE='"+headerTextColor+"'>");
		document.write("<PARAM NAME='headerBackgroundColor' VALUE='"+headerBackgroundColor+"'>");
		document.write("<PARAM NAME='drivesForegroundColor' VALUE='"+drivesForegroundColor+"'>");
		document.write("<PARAM NAME='drivesBackgroundColor' VALUE='"+drivesBackgroundColor+"'>");
		document.write("<PARAM NAME='ascBinTextColor' VALUE='"+ascBinTextColor+"'>");
		document.write("<PARAM NAME='buttonbackground' VALUE='"+buttonbackground+"'>");
		document.write("<PARAM NAME='language' VALUE='"+language+"'>");
		document.write("<PARAM NAME='classicfilelist' VALUE='"+classicfilelist+"'>");
		document.write("<PARAM NAME='helplocation' VALUE='"+helplocation+"'>");
		document.write("<PARAM NAME='LocalOptions' VALUE='"+LocalOptions+"'>");
		document.write("<PARAM NAME='RemoteOptions' VALUE='"+RemoteOptions+"'>");
		document.write("<PARAM NAME='stretchButtons' VALUE='"+stretchButtons+"'>");
		document.write("<PARAM NAME='display' VALUE='"+display+"'>");
		document.write("<PARAM NAME='showhelpbutton' VALUE='"+showhelpbutton+"'>");
		document.write("<PARAM NAME='showputbutton' VALUE='"+showputbutton+"'>");
		document.write("<PARAM NAME='showgetbutton' VALUE='"+showgetbutton+"'>");
		document.write("<PARAM NAME='showsyncbutton' VALUE='"+showsyncbutton+"'>");	
		document.write("<PARAM NAME='showaboutbutton' VALUE='"+showaboutbutton+"'>");	
		document.write("<PARAM NAME='showlocallist' VALUE='"+showlocallist+"'>");	
		document.write("<PARAM NAME='showremotelist' VALUE='"+showremotelist+"'>");	
		document.write("<PARAM NAME='errIEWinVM' VALUE='"+errIEWinVM+"'>");
		document.write("<PARAM NAME='selectalllocal' VALUE='"+selectalllocal+"'>");
		document.write("<PARAM NAME='selectallremote' VALUE='"+selectallremote+"'>");
		document.write("<PARAM NAME='autoupload' VALUE='"+autoupload+"'>");
		document.write("<PARAM NAME='autodownload' VALUE='"+autodownload+"'>");
		document.write("<PARAM NAME='autoallo' VALUE='"+autoallo+"'>");
		document.write("<PARAM NAME='rejectPermissionURL' VALUE='"+rejectPermissionURL+"'>");
		document.write("<PARAM NAME='encrypt' VALUE='"+encrypt+"'>");
		document.write("<PARAM NAME='ek' VALUE='"+ek+"'>");
		document.write("<PARAM NAME='createdirectoryonconnect' VALUE='"+createdirectoryonconnect+"'>");
		document.write("<PARAM NAME='autodetectproxy' VALUE='"+autodetectproxy+"'>");
		document.write("<PARAM NAME='socksproxy' VALUE='"+socksproxy+"'>");
		document.write("<PARAM NAME='socksProxyHost' VALUE='"+socksProxyHost+"'>");
		document.write("<PARAM NAME='socksProxyPort' VALUE='"+socksProxyPort+"'>");
		document.write("<PARAM NAME='ftpproxy' VALUE='"+ftpproxy+"'>");
		document.write("<PARAM NAME='ftpProxyHost' VALUE='"+ftpProxyHost+"'>");
		document.write("<PARAM NAME='ftpProxyPort' VALUE='"+ftpProxyPort+"'>");		
		document.write("<PARAM NAME='sotimeout' VALUE='"+sotimeout+"'>");		
		document.write("<PARAM NAME='connecttimeout' VALUE='"+connecttimeout+"'>");
		document.write("<PARAM NAME='enablerightclick' VALUE='"+enablerightclick+"'>");
		document.write("<PARAM NAME='hostsAllowed' VALUE='"+hostsAllowed+"'>");
		document.write("<PARAM NAME='remoteheader' VALUE='"+remoteheader+"'>");
		document.write("<PARAM NAME='SerfoLocation' VALUE='"+SerfoLocation+"'>");	
		document.write("<PARAM NAME='useSerfo' VALUE='"+useSerfo+"'>");
		document.write("<PARAM NAME='enablekeyboardshortcuts' VALUE='"+enablekeyboardshortcuts+"'>");
		document.write("<PARAM NAME='confirmoverwrite' VALUE='"+confirmoverwrite+"'>");
		document.write("<PARAM NAME='showsizeanddate' VALUE='"+showsizeanddate+"'>");
		document.write("<PARAM NAME='showSizeInKB' VALUE='"+showSizeInKB+"'>");
		document.write("<PARAM NAME='deleteoncancel' VALUE='"+deleteoncancel+"'>");
		document.write("<PARAM NAME='showlocaladdressbar' VALUE='"+showlocaladdressbar+"'>");
		document.write("<PARAM NAME='showremoteaddressbar' VALUE='"+showremoteaddressbar+"'>");				
		document.write("<PARAM NAME='waitRetry' VALUE='"+waitRetry+"'>");
		document.write("<PARAM NAME='maxRetries' VALUE='"+maxRetries+"'>");
		document.write("<PARAM NAME='bufSizeGet' VALUE='"+bufSizeGet+"'>");
		document.write("<PARAM NAME='bufSizePut' VALUE='"+bufSizePut+"'>");
		document.write("<PARAM NAME='enableHTTPResume' VALUE='"+enableHTTPResume+"'>");				
		document.write("<PARAM NAME='invertExclude' VALUE='"+invertExclude+"'>");
		document.write("<PARAM NAME='confirmTransfer' VALUE='"+confirmTransfer+"'>");
		document.write("<PARAM NAME='totalProgress' VALUE='"+totalProgress+"'>");
		document.write("<PARAM NAME='enableResume' VALUE='"+enableResume+"'>");
		document.write("<PARAM NAME='customFileOptions' VALUE='"+customFileOptions+"'>");
		document.write("<PARAM NAME='customDirOptions' VALUE='"+customDirOptions+"'>");
		document.write("<PARAM NAME='sendLogsToURL' VALUE='"+sendLogsToURL+"'>");		
		document.write("<PARAM NAME='showconnectbutton' VALUE='"+showconnectbutton+"'>");
		document.write("<PARAM NAME='showdisconnectbutton' VALUE='"+showdisconnectbutton+"'>");		
		document.write("<PARAM NAME='showFileInfoBar' VALUE='"+showFileInfoBar+"'>");
		document.write("<PARAM NAME='showStatusBar' VALUE='"+showStatusBar+"'>");								
		document.write("<PARAM NAME='preserveModificationTime' VALUE='"+preserveModificationTime+"'>");
		document.write("<PARAM NAME='removeAccentsAndQuotes' VALUE='"+removeAccentsAndQuotes+"'>");
		document.write("<PARAM NAME='removeSpaces' VALUE='"+removeSpaces+"'>");selectfileremote
		document.write("<PARAM NAME='selectfileremote' VALUE='"+selectfileremote+"'>");		
		document.write("<PARAM NAME='useToolbar' VALUE='"+useToolbar+"'>");
		document.write("<PARAM NAME='useBottomToolbar' VALUE='"+useBottomToolbar+"'>");
		document.write("<PARAM NAME='showTree' VALUE='"+showTree+"'>");
		document.write("<PARAM NAME='characterEncoding' VALUE='"+characterEncoding+"'>");

		for (n=0; n < numkeys; n++)
			document.write("<PARAM NAME='key"+(n+1)+"' VALUE='"+keys[n]+"'>");
										
		//if Java is disabled show an error message
      		document.write("<center><table width='90%' border='1' bordercolor='#000000'>");
      		document.write("<tr>");
      		document.write("<td bgcolor='#336633'>");
      		document.write("<div align='center'><font color='#FFFFFF'>Java is Disabled!</font></div>");
      		document.write("</td>");
      		document.write("</tr>");
      		document.write("<tr>");
      		document.write("<td>");
      		document.write("<table width='100%' border='0' cellpadding='0' cellspacing='20'>");
      		document.write("<tr>");
      		document.write("<td width='3%'><img src='error.gif' width='61' height='61'></td>");
      		document.write("<td width='97%'>");
      		document.write("<p>You must enable Java in your browser in order to upload files.</p>");
      		if (document.all) {
         		document.write("<p><b>To enable Java in Internet Explorer:</b></p>");
         		if (is_win)
            			document.write("<p>- Go to Tools - Internet Options<br>- Click on the Security Tag<br>- Select Medium Security Level for Internet Zone<br>- Reload this page</p>");
         		else if (is_mac)
            			document.write("<p>- Go to Edit - Preferences<br>- Click on Java<br>- Check \"Enable Java (Apple MRJ)\"<br>- Reload this page</p>");
        	}
      		else if (document.layers) {
         		document.write("<p><b>To enable Java in Netscape Navigator 4.X:</b></p>");
         		document.write("<p>- Go to Edit - Preferences<br>- Click on Advanced<br>- Check \"Enable Java\"<br>- Reload this page</p>");
      		}
      		else if (is_opera) {
         		document.write("<p><b>To enable Java in Opera:</b></p>");
         		document.write("<p>- Go to File - Preferences<br>- Click on Multimedia<br>- Check \"Enable Java\"<br>- Reload this page</p>");
      		}
      		document.write("</td>");
      		document.write("</tr>");
      		document.write("</table>");
      		document.write("</td>");
      		document.write("</tr>");
      		document.write("</table></center>");
      		//end of error message

  		if (is_ie && !isMacJaguar())
  			document.write("</OBJECT>");
  		else
			document.write("</APPLET>");

	   } else if (!appletWillRun()) {
		if (is_nav && is_win)  {
			window.location.href=errNavWin;			
		}
		else if (is_ie && is_win) {
			window.location.href=errIEWin;		
		}
		else if (is_nav && is_unix) {
			window.location.href=errNavUnix;
		}
		else if (is_ie && is_mac) {
			window.location.href=errIEMac;
		}
		else if (is_opera) { 
			window.location.href=errOperaWin;
		}					
	   }	
	}  // end non-Mac code
	else if (netmac==1){ //It's Netscape use the embed tag instead!
		if (is_mac)
	    		document.writeln("<EMBED  TYPE = 'application/x-java-vm' name='UnlimitedFTP' PLUGINSPAGE = 'http://www.mozilla.org/oji/' BORDER='0' code='"+classname+".class' height='"+height+"' width='"+width+"' archive='"+jar+"' ");
		else 
			document.writeln("<EMBED TYPE = 'application/x-java-applet;version=1.3' name='UnlimitedFTP' PLUGINSPAGE = 'http://java.sun.com/getjava/' BORDER='0' java_CODE='"+classname+"' height='"+height+"' width='"+width+"' java_CODEBASE = . java_ARCHIVE='"+jar+"' ");
		document.writeln(""); 
  		document.writeln("server='"+server+"'"); 
		document.writeln("port='"+port+"'");
		document.writeln("pass='"+pass+"'"); 
		document.writeln("user='"+user+"'"); 
		document.writeln("autoconnect='"+autoconnect+"'");
		document.writeln("autoreconnect='"+autoreconnect+"'");
		document.writeln("ascbin='"+ascbin+"'");
		document.writeln("showascbin='"+showascbin+"'");		
		document.writeln("asciiextensions='"+asciiextensions+"'"); 
		document.writeln("passive='"+passive+"'");
		document.writeln("extensions='"+extensions+"'");
		document.writeln("exclude='"+exclude+"'");
		document.writeln("lockinitialdir='"+lockinitialdir+"'"); 
		document.writeln("remotedir='"+remotedir+"'");
		document.writeln("localdir='"+localdir+"'"); 
		document.writeln("enableCookies='"+enableCookies+"'"); 
		document.writeln("doubleClickTransfer='"+doubleClickTransfer+"'"); 
		document.writeln("syncpriority='"+syncpriority+"'"); 
		document.writeln("incremental='"+incremental+"'"); 
		document.writeln("incdatetime='"+incdatetime+"'");
		document.writeln("timezonecomp='"+timezonecomp+"'");
		document.writeln("background='"+background+"'"); 
		document.writeln("buttonTextColorOnMouseOver='"+buttonTextColorOnMouseOver+"'");
		document.writeln("buttonTextColor='"+buttonTextColor+"'");
		document.writeln("buttonColorOnMouseOver='"+buttonColorOnMouseOver+"'"); 
		document.writeln("headerTextColor='"+headerTextColor+"'"); 
		document.writeln("headerBackgroundColor='"+headerBackgroundColor+"'");
		document.writeln("drivesForegroundColor='"+drivesForegroundColor+"'"); 
		document.writeln("drivesBackgroundColor='"+drivesBackgroundColor+"'"); 
		document.writeln("ascBinTextColor='"+ascBinTextColor+"'"); 
		document.writeln("buttonbackground='"+buttonbackground+"'");		
		document.writeln("language='"+language+"'");
		document.writeln("classicfilelist='"+classicfilelist+"'");
		document.writeln("helplocation='"+helplocation+"'"); 
		document.writeln("LocalOptions='"+LocalOptions+"'");
		document.writeln("RemoteOptions='"+RemoteOptions+"'");
		document.writeln("stretchButtons='"+stretchButtons+"'");
		document.writeln("display='"+display+"'");
		document.writeln("showhelpbutton='"+showhelpbutton+"'"); 
		document.writeln("showputbutton='"+showputbutton+"'");
		document.writeln("showgetbutton='"+showgetbutton+"'");		
		document.writeln("showsyncbutton='"+showsyncbutton+"'");	
		document.writeln("showaboutbutton='"+showaboutbutton+"'");	
		document.writeln("showlocallist='"+showlocallist+"'");	
		document.writeln("showremotelist='"+showremotelist+"'");	
		document.writeln("errIEWinVM='"+errIEWinVM+"'");
		document.writeln("selectalllocal='"+selectalllocal+"'");
		document.writeln("selectallremote='"+selectallremote+"'");
		document.writeln("autoupload='"+autoupload+"'");
		document.writeln("autodownload='"+autodownload+"'");
		document.writeln("autoallo='"+autoallo+"'");
		document.writeln("rejectPermissionURL='"+rejectPermissionURL+"'");
		document.writeln("encrypt='"+encrypt+"'");
		document.writeln("ek='"+ek+"'");
		document.writeln("createdirectoryonconnect='"+createdirectoryonconnect+"'");
		document.writeln("autodetectproxy='"+autodetectproxy+"'");
		document.writeln("socksproxy='"+socksproxy+"'");
		document.writeln("socksProxyHost='"+socksProxyHost+"'");
		document.writeln("socksProxyPort='"+socksProxyPort+"'");
		document.writeln("ftpproxy='"+ftpproxy+"'");
		document.writeln("ftpProxyHost='"+ftpProxyHost+"'");
		document.writeln("ftpProxyPort='"+ftpProxyPort+"'");	
		document.writeln("sotimeout='"+sotimeout+"'");	
		document.writeln("connecttimeout='"+connecttimeout+"'");
		document.writeln("enablerightclick='"+enablerightclick+"'");		
		document.writeln("remoteheader='"+remoteheader+"'");		
		document.writeln("SerfoLocation='"+SerfoLocation+"'");
		document.writeln("useSerfo='"+useSerfo+"'");
		document.writeln("hostsAllowed='"+hostsAllowed+"'");
		document.writeln("showsizeanddate='"+showsizeanddate+"'");	
		document.writeln("showSizeInKB='"+showSizeInKB+"'");
		document.writeln("deleteoncancel='"+deleteoncancel+"'");
		document.writeln("enablekeyboardshortcuts='"+enablekeyboardshortcuts+"'");
		document.writeln("confirmoverwrite='"+confirmoverwrite+"'"); 		
		document.writeln("showremoteaddressbar='"+showremoteaddressbar+"'"); 
		document.writeln("showlocaladdressbar='"+showlocaladdressbar+"'"); 			
		document.writeln("waitRetry='"+waitRetry+"'");
		document.writeln("maxRetries='"+maxRetries+"'");
		document.writeln("bufSizeGet='"+bufSizeGet+"'");
		document.writeln("bufSizePut='"+bufSizePut+"'");
		document.writeln("enableHTTPResume='"+enableHTTPResume+"'");
		document.writeln("invertExclude='"+invertExclude+"'");
		document.writeln("confirmTransfer='"+confirmTransfer+"'");
		document.writeln("totalProgress='"+totalProgress+"'");
		document.writeln("enableResume='"+enableResume+"'");
		document.writeln("customFileOptions='"+customFileOptions+"'");
		document.writeln("customDirOptions='"+customDirOptions+"'");
		document.writeln("sendLogsToURL='"+sendLogsToURL+"'");
		document.writeln("showconnectbutton='"+showconnectbutton+"'");
		document.writeln("showdisconnectbutton='"+showdisconnectbutton+"'");
		document.writeln("showFileInfoBar='"+showFileInfoBar+"'");
		document.writeln("showStatusBar='"+showStatusBar+"'");											
		document.writeln("preserveModificationTime='"+preserveModificationTime+"'");
		document.writeln("removeAccentsAndQuotes='"+removeAccentsAndQuotes+"'");	
		document.writeln("removeSpaces='"+removeSpaces+"'");	
		document.writeln("selectfileremote='"+selectfileremote+"'");
		
		document.writeln("useToolbar='"+useToolbar+"'");
		document.writeln("useBottomToolbar='"+useBottomToolbar+"'");
		document.writeln("showTree='"+showTree+"'");
		document.writeln("characterEncoding='"+characterEncoding+"'");
		
		for (n=0; n < numkeys; n++)
			document.write("key"+(n+1)+"='"+keys[n]+"'");									
		document.writeln(">"); 
	}
	else if (netmac==2) {//Netscape doesn't have the MRJ Plugin.
		window.location.href=errNavMac;
	}
