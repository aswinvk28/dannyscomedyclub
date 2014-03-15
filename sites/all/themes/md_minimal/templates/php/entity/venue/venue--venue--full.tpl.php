<div class="clearfix">
    <span>Venue: </span>
    <p><?php print l($title, $url); ?></p>
</div>

<section class="clearfix">
    <?php if(!empty($venue_fields['address'])) { ?>
    <address>
        <span>Address: </span>
        <?php print $venue_fields['address']; ?>
    </address>
    <?php } if(!empty($venue_fields['telephone'])) { ?>
        <span>Telephone: </span>
        <p><?php print $venue_fields['telephone']; ?></p>
    <?php } if(!empty($venue_fields['url'])) { ?>
        <span>Venue Website: </span>
        <p><?php print l($title, $venue_fields['url']); ?></p>
    <?php } ?>
    <div class="row-fluid">
        <div class="span9">
            <?php print $venue_fields['body']; ?>
            <map class="clearfix">
                <span id="map_lat" class="hidden"><?php print $venue_fields['map_lat']; ?></span>
                <span id="map_long" class="hidden"><?php print $venue_fields['map_long']; ?></span>
                <div id="map_container" class="clearfix column_small border_radius_large"></div>
            </map>
        </div>
    </div>
</section>