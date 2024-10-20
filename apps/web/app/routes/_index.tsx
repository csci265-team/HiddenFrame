/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { useLoaderData } from "@remix-run/react";
import PageHeader from "../components/PageHeader";

export const meta: MetaFunction = () => {
  return [
    { title: "HiddenFrame" },
    { name: "description", content: "Welcome to Remix!" },
  ];
};

export async function loader() {
  const resp = await fetch("https://api.unsplash.com/photos?per_page=1000", {
    headers: { Authorization: `Client-ID ${process.env.UNSPLASH_ACCESS_KEY}` },
  });

  if (resp.ok) return { photos: await resp.json() };
  else return { photos: [] };
}

export default function Index() {
  const { photos } = useLoaderData<typeof loader>();

  return (
    <div className="flex items-center justify-center h-full">
      <div className="flex flex-col items-center gap-16 h-full">
        <PageHeader />

        <h2 className="text-2xl font-[Outfit] font-black ">Photos from Unsplash</h2>
        <div className="grid grid-cols-3 gap-4 p-4">
          {photos.map((photo: any) => (
            <a href={photo.urls.full} target="_blank" key={photo.id} rel="noreferrer">
              <img className="w-64 h-64 rounded-lg object-cover" src={photo.urls.small} alt={photo.alt_description} />
            </a>
          ))}
        </div>
      </div>
    </div>
  );
}

