<div class="<?php echo $classes; ?>" <?php print $attributes; ?> itemprop="video" itemscope itemtype="http://schema.org/VideoObject">
    <meta itemprop="url" content="http://www.youtube.com/watch?v=<?php echo $video_id; ?>"/>
    
    <meta itemprop="caption" content="<?php echo $title; ?>"/>
    <?php if(!empty($image_url)) { ?>
    <span itemprop="thumbnail" itemscope itemtype="http://schema.org/ImageObject">
        <meta itemprop="image" content="<?php echo file_create_url($image_url); ?>"/>
    </span>
    <?php } ?>
    <object class="iframe_video" style="display: block; width: 560px; height: 315px">
      <param name="movie"
             value="https://www.youtube.com/v/<?php echo $video_id; ?>?version=3&autoplay=0"></param>
      <param name="allowScriptAccess" value="always"></param>
      <embed src="https://www.youtube.com/v/<?php echo $video_id; ?>?version=3&autoplay=0&wmode=opaque"
             type="application/x-shockwave-flash"
             allowscriptaccess="always" wmode="opaque" allowfullscreen="true" style="display: block; width:100%; height: 100%"></embed>
    </object>
</div>