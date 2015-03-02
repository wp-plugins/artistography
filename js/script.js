var $ = jQuery.noConflict();

$(document).ready(function() {
    var $tabs = $('#tabs').tabs({ fx: { opacity: 'toggle', height: 'toggle', width: 'toggle' } }).slideDown();

    if ( $( "#accordion1" ).length != 0 ) $( "#accordion1" ).accordion({ autoHeight: false});
    if ( $( "#accordion2" ).length != 0 ) $( "#accordion2" ).accordion({ autoHeight: false});
    if ( $( "#accordion3" ).length != 0 ) $( "#accordion3" ).accordion({ autoHeight: false});
    if ( $( "#accordion4" ).length != 0 ) $( "#accordion4" ).accordion({ autoHeight: false});

    $(".colorbox").colorbox({scalePhotos:true, maxWidth: '90%', maxHeight: '90%', slideshow:true});

    $('.artist_table').slideDown();

    $('.qitem')
	.hover(
		function() {
			$(this).find('img').fadeOut();
		}, function(){
        	        $(this).find('img').fadeIn(1000);
   		}
    	);

	soundManager.setup({
		url: '../soundmanagerv297a-20140901/swf/',
		flashVersion: 9, // optional: shiny features (default = 8)
		 // optional: ignore Flash where possible, use 100% HTML5 mode
		 //preferFlash: false,

		onready: function() {
		 // Ready to use; soundManager.createSound() etc. can now be called.
		}
	});
});

      function loadAlbumArt(song_id) {
          var data = {
                  action: 'Load_Album_Art',
                  song_id: song_id
          };
          $.post(MyAjax.ajaxurl, data, function(response) {
              $( "#sm2-album-art" ).attr('src', response);
              $( "#sm2-album-art" ).attr('height', '100%');
	      var height = $( "#sm2-album-art" ).height();
              $("#sm2-album-art" ).attr('width', height);
          });
      }

      function loadAlbumArtRefresh(height) {
              $( "#sm2-album-art" ).attr('height', height);
              $("#sm2-album-art" ).attr('width', height);
      }
