(function ($) {

Drupal.behaviors.slider = {
    attach:function(context) {
        
      var maxWidth = Drupal.settings.views_horizontal_slider.max_width;
      var minWidth = Drupal.settings.views_horizontal_slider.min_width;
      var caption_field = Drupal.settings.views_horizontal_slider.caption_field_name;

      /* the animations are saved as strings via fapi, but somehow duration explicitly wants an int*/
      var caption_fadein = parseInt(Drupal.settings.views_horizontal_slider.caption_field_fadeout);
      var caption_fadeout = parseInt(Drupal.settings.views_horizontal_slider.caption_field_fadein);
        
      var lastBlock = $('.views_horizontal_slider div.item-list li.hslider-active');

      /* the animations are saved as strings via fapi, but somehow duration explicitly wants an int*/
      var animate_in = parseInt(Drupal.settings.views_horizontal_slider.animate_in);
      var animate_out = parseInt(Drupal.settings.views_horizontal_slider.animate_out);

      $('.views_horizontal_slider div.item-list li').hover(
        function(){
          $(lastBlock).animate({width: minWidth+'px'}, { queue:false, duration:animate_in});
          $(this).animate({width: maxWidth+'px'}, { queue:false, duration:animate_out});

              if(caption_field) {
                  $(this).children('.'+caption_field).fadeIn(caption_fadein);
              }
              else {}

          lastBlock = this;
        },
        function(){

            if(caption_field) {
                $(lastBlock).children('.'+caption_field).fadeOut(caption_fadeout);
            }
            else {}

        }
      );

    }

};


}(jQuery));



