var $ = jQuery.noConflict();

$(document).ready(function() {
    var $tabs = $('#tabs').tabs({ fx: { opacity: 'toggle', height: 'toggle', width: 'toggle' } }).slideDown();

    if ( $( "#accordion1" ).length != 0 ) $( "#accordion1" ).accordion({ autoHeight: false});
    if ( $( "#accordion2" ).length != 0 ) $( "#accordion2" ).accordion({ autoHeight: false});
    if ( $( "#accordion3" ).length != 0 ) $( "#accordion3" ).accordion({ autoHeight: false});
    if ( $( "#accordion4" ).length != 0 ) $( "#accordion4" ).accordion({ autoHeight: false});

	function LoadShoppingCart() {
	    var data = {
	        action: 'Get_Cart_Contents'
	    };
	    $.post(MyAjax.ajaxurl, data, function(response) {
	    	$(".artistography_cart").empty().append(response);
		$('html, body').animate({
		    scrollTop: $(".widget_artistography_cart_widget").offset().top
		}, 2000);

		     /* Delete From Cart Button */
		    $( ".remove_from_cart" ).button({
		        text: true,
		        icons: {
		            primary: "ui-icon-trash"
		        }    }).click(function() {
		        var id = $( this ).attr('id');
		          var data = {
		                  action: 'Remove_From_Cart',
        		          product: id
		          };
		          $.post(MyAjax.ajaxurl, data, function(response) {
		                LoadShoppingCart();
        		  });
    		});
	    });
	}
	LoadShoppingCart();

     /* Edit Shopping Cart Button */
    $( ".edit_cart" ).button({
        text: true,
        icons: {
            primary: "ui-icon-cart"
        }
    }).click(function() {
	/* Do AJAX call to get URL of cart and go there */
	  var data = {
                  action: 'Get_Cart_URL'
          };
          $.post(MyAjax.ajaxurl, data, function(response) {
		location.assign(response);
          });
    });

     /* Buy Song Button */
    $( ".song_to_cart" ).button({
        text: true,
        icons: {
            primary: "ui-icon-cart"
        }
    }).click(function() {
        var id = $( this ).attr('id').replace('song_download_', '');
          var data = {
                  action: 'Add_Song_To_Cart',
		  song_id: id
          };
          $.post(MyAjax.ajaxurl, data, function(response) {
                LoadShoppingCart();
          });
    });

     /* Buy Album Download Button */
    $( ".album_download_to_cart" ).button({
        text: false,
        icons: {
            primary: "ui-icon-cart"
        }
    }).click(function() {
        var id = $( this ).attr('id').replace('album_download_', '');
          var data = {
                  action: 'Add_Album_Download_To_Cart',
                  album_id: id
          };
          $.post(MyAjax.ajaxurl, data, function(response) {
                LoadShoppingCart();
          });
    });

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
