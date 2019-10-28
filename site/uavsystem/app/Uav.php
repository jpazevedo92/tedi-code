<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Uav extends Model
{
    public function networks()
    {
        return $this->hasMany(Network::class);
    }
    
    public function mpls_tags()
    {
        return $this->hasMany(MplsTag::class);
    }
}
