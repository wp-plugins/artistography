var $ = jQuery.noConflict();


(function($) {
   jQuery.fn.backgroundPosition = function() {
     var p = $(this).css('background-position');
     if(typeof(p) === 'undefined') return $(this).css('background-position-x') + ' ' + $(this).css('background-position-y');
     else return p;
   };
 })(jQuery); 


$(document).ready(function() {
    var $tabs = $('#tabs').tabs({ fx: { opacity: 'toggle', height: 'toggle', width: 'toggle' } }).slideDown();

    if ( $( "#accordion1" ).length != 0 ) $( "#accordion1" ).accordion({ autoHeight: false});
    if ( $( "#accordion2" ).length != 0 ) $( "#accordion2" ).accordion({ autoHeight: false});
    if ( $( "#accordion3" ).length != 0 ) $( "#accordion3" ).accordion({ autoHeight: false});

    $('.artist_table').slideDown();

    //Custom settings
    var style_in = 'easeOutBounce';
    var style_out = 'jswing';
    var speed_in = 1000;
    var speed_out = 300;    

    //Calculation for corners
    var neg = Math.round($('.qitem').width() / 2) * (-1);   
    var pos = neg * (-1);   
    var out = pos * 2;

    $('.qitem').each(function () {

        //grab the anchor and image path
        url = $(this).find('a').attr('href');
        img = $(this).find('img').attr('src');
        img_size = $(this).find('img').attr('width');
        new_img = 'artistography/wp-content/plugins/artistography/css/images/ajax-loader.gif';

        //remove the image
        $('img', this).remove();

        //append four corners/divs into it
        $(this).append('<div class="topLeft"></div><div class="topRight"></div><div class="bottomLeft"></div><div class="bottomRight"></div>');
         
        if (navigator.appName=='Microsoft Internet Explorer') {
          $(this).find('div.topLeft').append('<img src="' + img + '" style="position:absolute;height:200%;width:200%;top:0px;left:0px;" />');
          $(this).find('div.topRight').append('<img src="' + img + '" style="border:0px;position:absolute;height:200%;width:200%;top:0px;left:' + neg + 'px;" />');
          $(this).find('div.bottomLeft').append('<img src="' + img + '" style="border:0px;position:absolute;height:200%;width:200%;top:' + neg + 'px;left:0px;" />');
          $(this).find('div.bottomRight').append('<img src="' + img + '" style="border:0px;position:absolute;height:200%;width:200%;top:' + neg + 'px;left:' + neg + 'px;" />');
        } else {
          //set the background image to all the corners
          $(this).children('div').css('background-image','url("'+ img + '")');
          //set the background image to all the corners
          $(this).children('div').css('background-size','200%');
        }

        if (navigator.appName=='Microsoft Internet Explorer') {
          //set the position of corners
          $(this).find('div.topLeft').css({top:0, left:0, width:pos , height:pos});
          $(this).find('div.topRight').css({top:0, left:pos, width:pos , height:pos});
          $(this).find('div.bottomLeft').css({bottom:1, left:0, width:pos , height:pos});
          $(this).find('div.bottomRight').css({bottom:1, left:pos, width:pos , height:pos}); 
        } else {
          //set the position of corners
          $(this).find('div.topLeft').css({top:0, left:0, width:pos , height:pos});
          $(this).find('div.topRight').css({top:0, left:pos, width:pos , height:pos});
          $(this).find('div.bottomLeft').css({bottom:0, left:0, width:pos , height:pos});
          $(this).find('div.bottomRight').css({bottom:0, left:pos, width:pos , height:pos}); 
        }
    }).hover(function () {
        //animate the position
        $(this).find('div.topLeft').stop(false, true).animate({top:neg, left:neg}, {duration:speed_out, easing:style_out}); 
        $(this).find('div.topRight').stop(false, true).animate({top:neg, left:out}, {duration:speed_out, easing:style_out});    
        $(this).find('div.bottomLeft').stop(false, true).animate({bottom:neg, left:neg}, {duration:speed_out, easing:style_out});   
        $(this).find('div.bottomRight').stop(false, true).animate({bottom:neg, left:out}, {duration:speed_out, easing:style_out});  
    },

    function () {
        if (navigator.appName=='Microsoft Internet Explorer') {
          //put corners back to the original position
          $(this).find('div.topLeft').stop(false, true).animate({top:0, left:0}, {duration:speed_in, easing:style_in});   
          $(this).find('div.topRight').stop(false, true).animate({top:0, left:pos}, {duration:speed_in, easing:style_in});    
          $(this).find('div.bottomLeft').stop(false, true).animate({bottom:1, left:0}, {duration:speed_in, easing:style_in}); 
          $(this).find('div.bottomRight').stop(false, true).animate({bottom:1, left:pos}, {duration:speed_in, easing:style_in});  
        } else {
          //put corners back to the original position
          $(this).find('div.topLeft').stop(false, true).animate({top:0, left:0}, {duration:speed_in, easing:style_in});   
          $(this).find('div.topRight').stop(false, true).animate({top:0, left:pos}, {duration:speed_in, easing:style_in});    
          $(this).find('div.bottomLeft').stop(false, true).animate({bottom:0, left:0}, {duration:speed_in, easing:style_in}); 
          $(this).find('div.bottomRight').stop(false, true).animate({bottom:0, left:pos}, {duration:speed_in, easing:style_in});  
        }
    }).click (function () {
        //go to the url
        window.location = $(this).find('a').attr('href');
        $(this).hide("explode", 1000);
    });

});
