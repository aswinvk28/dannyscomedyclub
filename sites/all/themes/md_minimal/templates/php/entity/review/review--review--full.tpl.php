<article class="<?php print $classes; ?>" <?php print $attributes; ?> itemscope itemtype="http://schema.org/Review" itemprop="review">
    
    <?php if(!empty($review['name'])) { ?>
    <div class="clearfix column">
        <span class="white">Title:</span>
        <meta itemprop="name" value="<?php print $review['name']; ?>" />
        <meta itemprop="url" value="<?php print $url; ?>" />
        <div class="clearfix column_small">
        <?php print theme('list_item_view', array(
            'ul_class' => 'act-tags',
            'li_class' => 'act-tag pull-left white',
            'items' => array(
                array(
                    'content' => '<a class="underline" href="'.$url.'">'.$review['name'].'</a>'
                )
            )
        )); ?>
        </div>
    </div>
    <?php } ?>
    
    <div class="clearfix column">
        <span class="white">Review For:</span>
        <div itemprop="itemReviewed" itemscope itemtype="http://schema.org/Thing">
            <meta itemprop="url" value="<?php print $review['reference_path']; ?>" />
            <meta itemprop="name" value="<?php print $review['reference_title']; ?>" />
        </div>
        <div class="clearfix column_small">
        <?php print theme('list_item_view', array(
            'ul_class' => 'act-tags',
            'li_class' => 'act-tag pull-left white',
            'items' => array(
                array(
                    'content' => '<a class="underline" href="'.$review['reference_path'].'">'.$review['reference_title'].'</a>'
                )
            )
        )); ?>
        </div>
    </div>
    
    <?php if(!empty($review['author'])) { ?>
    <div class="clearfix column">
        <span class="white">Review Author:</span>
        <div class="clearfix column_small">
            <span><?php print $review['author']; ?></span>
        </div>
    </div>
    <?php } ?>
    
    <?php if(!empty($review['date'])) { ?>
    <div class="clearfix column">
        <span class="white">Review Date:</span>
        <div class="clearfix column_small">
            <span><?php print $review['date']; ?></span>
        </div>
    </div>
    <?php } ?>
    
    <div class="clearfix column bg-gray padding-20">
        <span class="white">Review:</span>
        <div class="clearfix column_small white" itemprop="reviewBody">
        <?php print $review['description']; ?>
        </div>
    </div>
    
</article>