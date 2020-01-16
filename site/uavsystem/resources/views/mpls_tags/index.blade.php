@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.mpls_tag') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.mpls_tag') }}
@endsection

@section('content')
    @include('mpls_tags.mpls_tags_table')
@endsection
